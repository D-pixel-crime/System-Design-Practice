#include "../include/dispatcher.hpp"
#include "../include/notifier.hpp"
#include <iostream>

Dispatcher::Dispatcher(Message_Queue *_queue) : queue(_queue) {}

void Dispatcher::pullNotification() {
  while (true) {
    RetryItem item{nullptr, std::chrono::steady_clock::now(),
                   std::chrono::milliseconds(0)};

    {
      std::unique_lock<std::mutex> lock(queue->mtx);

      queue->cv.wait(lock, [this]() { return queue->hasReadyItem(); });

      item = queue->popReadyItem();
    }

    if (item.notification) {
      try {
        deployNotification(item.notification);
      } catch (const std::exception &e) {
        std::cerr << "Dispatch failed, pushing to retry queue: " << e.what()
                  << '\n';
        queue->pushFailed(item);
      }
    }
  }
}

void Dispatcher::deployNotification(Notification *_notification) const {
  auto [product, user, method] = _notification->getNotificationDetails();
  method->processNotification(product, user);

  Notifier::getNotifier()->restoreNotification(_notification);
}