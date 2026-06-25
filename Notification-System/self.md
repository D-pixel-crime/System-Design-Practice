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
  -  `cnt/status`: This is just a notification system, so we do not need to have individual objects of each product.
  -  `updateCnt()/updateStatus()`: Changes the status/cnt of the product and pushes notifications if necessary.
  -  `getAvailability()`: Query (pull) for availability requested by the user.
### **_Class_ Notification**:
  - `product`
  - `subscriber`
  - `method`
### **_Interface_ Notification_Method**:
  - `processNotification()`: Must to be implemented method that carries out a notification in a particular way.
### **_Interface_ Notifier**:
  - `notify(product, user, method)`: Schedules a single notification for a particular notification method.
  - `notifyAll(product)`: Schedules notifications for list of users with all their opted notification methods for a particular product.
### **_Interface/Class_ User**:
  - `products -> (list)notification_options/methods`*(map)*: All the products the user is interested in and their respective notification-options/methods.
  - `getStatus(product)`: Queries the availability for a **subscribed** product.
### **_Class_ Message_Queue**:
  - `size`: Constant size of queues during initialisation. Queues should be size initialised to protect against back-pressure.
  - `push_queue(Notification)(constant size)`***Study Ring Buffers***: Queue, that stores incoming notifications to be pushed to the user.
  - `retry_queue(Notification, wait_time)(constant size)`***Study Ring Buffers***: Queue for storing failed notifications. Each missed push should increase the wait time upto certain limit, until finally dropping it.
### **_Class_ Queue_Pool/Slab_Allocator _(Singleton Pattern)_**:
  - `static total_queues`: The total number of objects creatable for `Message_Queue` Class.
  - `queue_pool`*(list of `Message_Queue`)*: Implement the idea of SLAB ALLOCATOR. Instead of allocating and destroying objects, hand over available queue. If not available, simply deny request or **some other fallback**.
  - `allocate_queue()`: Hands over available queue(if any) from the `queue_pool`.
  - `restore_queue(queue)`: Clears the `queue` and adds it back to the availabilities in `queue_pool`.
### **_Class_ Worker/Dispatcher**:
  - ***A thread which is asleep until message_queue is empty, else would take the first Notification from the queue and process it.***
  - `push(Notification)`: Pushes the current passed notification.