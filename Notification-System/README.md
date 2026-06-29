# Notification System

## Functional Requirements
- There should be a product (or) list of products.
- Ability to track subscribers for a product.
- Should have multiple methods/ways of sending the notification.
- Each subscriber should have the freedom to choose/drop single/multiple methods of notification.
- Notification should be sent to each subscriber via all opted methods.
- **On-Demand Product Status (Pull Mechanism):** Store and update current status of each product. Subscribers must be able to directly query (pull) this information at any time.
- **Ability to trigger or create a new notification when a product event happens (e.g., "back in stock" or "price drop").**
- How to optimally implement these?

## Non-Functional Requirements (System Safety & Scale)
- **No Duplicate Messages:** User should never receive the exact same notification again through the same method.
- **Smart Retries:** If a message fails to send (e.g., the external email provider is temporarily down), the system should wait and try again. The wait time should increase in each attempt.
- **Handling Unsendable Messages:** If a message fails completely after several tries (e.g., the user has a fake email address), **the system shouldn't freeze or crash**. It should quietly move that message to a "failed" list to be checked later.
- **Preventing Overload:** If a product goes viral and 100,000 notifications need to go out at the exact same time, the system must send them at a steady, controlled pace so the external email/text providers don't block us for spamming.

## Possible Interfaces/Classes
### **_Interface_ Product**:
  - `cnt`: Current count of the product.
  - `updateCount(const int &_newCnt)`: Changes the status/cnt of the product and pushes notifications if necessary.
  - `getAvailability()`: Query (pull) for availability requested by the user.
  - `getName()`: Returns the name of the product.
### **_Class_ Notification**:
  - `product`
  - `subscriber`
  - `notificationMethod`
  - `reset()`: Resets the notification details.
  - `update(product, subscriber, method)`: Populates the notification with new details.
  - `getNotificationDetails()`: Returns a tuple containing the product, subscriber, and method.
### **_Interface_ Notification_Method**:
  - `processNotification(I_Product*, I_User*)`: Must to be implemented method that carries out a notification in a particular way.
### **_Interface_ Notifier**:
  - `notify(product, user, method)`: Schedules a single notification for a particular notification method.
  - `notifyAll(product)`: Schedules notifications for list of users with all their opted notification methods for a particular product.
  - `getAvailableNotification()`: *(Current Implementation: Fetches a pre-allocated Notification object from a fixed-size pool to prevent memory exhaustion).*
  - `restoreNotification(Notification)`: *(Current Implementation: Restores the Notification object back to the pool once completely processed or permanently failed).*
  - `pushToQueue(product, user, method)`: Internal method that retrieves a notification from the pool, populates it, and pushes it.
### **_Class_ Database**:
  - `products`*(set)*
  - `users`*(set)*
  - `subscriptions`*(map of (Product -> map of (User -> set of Methods)))*
  - `database_mutex`
  - `getConn()`: Returns the singleton Database instance.
  - `registerProduct(Product)`
  - `registerUser(User)`
  - `subscribeUser(Product, User, Notification_Method)`
  - `unsubscribeUser(Product, User, Notification_Method)`
  - `getPreferences(Product, User)`: Returns the whole list of methods for User. If User is NULL, returns all the Users and their methods.
### **_Interface/Class_ User**:
  - `id`: Unique user identifier.
  - `getStatus(product)`: Queries the availability for a **subscribed** product.
  - `addNotificationMethod(Product, Notification_Method)`: Just forward a request to `Database` for updating the User's preferences.
  - `getId()`: Returns the user's ID.
### **_Class_ Message_Queue**:
  - `size`: Constant size of queues during initialisation. Queues should be size initialised to protect against back-pressure.
  - `push_queue`*(queue)*: Queue that stores incoming notifications to be pushed to the user.
  - `retry_queue`*(priority queue)*: Queue for storing failed notifications as `RetryItem`s sorted by deadline.
  - `pushNotification(Notification)`: Securely locks the queue and pushes a new notification, signaling the condition variable.
  - `pushFailed(RetryItem)`: Pushes a failed notification to the `retry_queue` with exponential backoff until permanent failure.
  - `popReadyItem()`: Pops a ready item from `retry_queue` or `push_queue` for the dispatcher to process.
  - `hasReadyItem()`: Checks if there are items ready to be processed.
### **_Class_ Queue_Pool/Slab_Allocator _(Singleton Pattern)_**:
  - `static total_queues`: The total number of objects creatable for `Message_Queue` Class.
  - `queuePool`*(priority queue of `Message_Queue`)*: *(Current Implementation: Acts as a load balancer by handing over the least loaded queue using a Min-Heap).*
  - `createQueuePool(totalQueues, queueSize)`: Initializes the singleton and creates the pool of queues.
  - `allocate_queue()`: Hands over the least loaded queue from the `queuePool`.
### **_Class_ Worker/Dispatcher**:
  - `queue`: Pointer to the `Message_Queue` this dispatcher pulls from.
  - `pullNotification()`: *(Current Implementation: Thread-safe polling loop that pulls from `Message_Queue` using condition variables).*
  - `deployNotification(Notification)`: *(Current Implementation: Dispatches the notification. If it throws an exception, gracefully pushes to `retry_queue`).*

## Architecture Diagram

![Notification System UML](Notification%20System%20UML.drawio.svg)