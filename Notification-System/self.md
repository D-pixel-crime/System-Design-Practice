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