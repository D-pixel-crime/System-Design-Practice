#include "../include/notifier.hpp"
#include "../include/database.hpp"
#include "../include/queueAllocator.hpp"
#include <mutex>

Notifier::Notifier(int _totalNotifications)
{
    while (_totalNotifications--)
    {
        notificationPool.push_back(new Notification());
    }

    total_notifications = notificationPool.size();
}

Notifier *Notifier::getNotifier(const int &_totalNotifications)
{
    {
        std::unique_lock<std::mutex> lock(notifier_mtx);

        if (!notifier)
        {
            notifier = new Notifier(_totalNotifications);
        }
    }
    return notifier;
}

void Notifier::pushToQueue(I_Product *_product, I_User *_user, I_Notification_Method *_notificationMethod)
{
    Notification *currNotification = getAvailableNotification();
    currNotification->update(_product, _user, _notificationMethod);

    Queue_Allocator::allocate_queue()->pushNotification(currNotification);
}

void Notifier::restoreNotification(Notification *_notification)
{
    _notification->reset();
    {
        std::unique_lock<std::mutex> lock(pool_mtx);

        if (total_notifications == notificationPool.size())
        {
            delete _notification;
            return;
        }
        notificationPool.push_back(_notification);
    }

    pool_cv.notify_one();
}

Notification *Notifier::getAvailableNotification()
{
    Notification *currNotification = nullptr;

    {
        std::unique_lock<std::mutex> lock(pool_mtx);

        pool_cv.wait(lock, [this]()
                     { return !notificationPool.empty(); });

        currNotification = notificationPool.back();
        notificationPool.pop_back();
    }

    return currNotification;
}

void Notifier::notify(I_Product *_product, I_User *_user, I_Notification_Method *_notificationMethod)
{
    if (!_product || !_user)
    {
        return;
    }

    Database *db = Database::getConn();
    auto subscriptions = db->getPreferences(_product, _user);
    if (subscriptions.empty() || !subscriptions.count(_user))
    {
        return;
    }

    if (_notificationMethod)
    {
        if (!subscriptions[_user].count(_notificationMethod))
        {
            pushToQueue(_product, _user, _notificationMethod);
        }

        return;
    }

    for (auto &method : subscriptions[_user])
    {
        pushToQueue(_product, _user, method);
    }
}

void Notifier::notifyAll(I_Product *_product)
{
    if (!_product)
    {
        return;
    }

    Database *db = Database::getConn();
    auto subscriptions = db->getPreferences(_product);

    for (auto &[user, userMethods] : subscriptions)
    {
        for (auto &method : userMethods)
        {
            pushToQueue(_product, user, method);
        }
    }
}