#include "../include/notifier.hpp"
#include <mutex>

std::mutex notifier_mutex;

Notifier::Notifier(int _totalNotifications)
{
    while (_totalNotifications--)
    {
        notificationPool.push_back(new Notification());
    }
}

Notifier *Notifier::createNotificationPool(const int &_totalNotifications)
{
    {
        std::lock_guard<std::mutex> lock(notifier_mutex);

        if (!notifier)
        {
            notifier = new Notifier(_totalNotifications);
        }
    }
    return notifier;
}