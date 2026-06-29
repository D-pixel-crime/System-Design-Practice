#pragma once
#include "../interfaces/I_Notifier.hpp"
#include "../interfaces/I_Product.hpp"
#include "notification.hpp"
#include <vector>
#include <mutex>
#include <condition_variable>

class Notifier : public I_Notifier
{
private:
    inline static std::mutex notifier_mtx;
    inline static std::mutex pool_mtx;
    inline static std::condition_variable pool_cv;

    inline static int total_notifications = 0;
    inline static Notifier *notifier = nullptr;
    inline static std::vector<Notification *> notificationPool;

    Notifier() = delete;
    Notifier(int _totalNotifications);

    void pushToQueue(I_Product *_product, I_User *_user, I_Notification_Method *_notificationMethod);

    Notification *getAvailableNotification();

public:
    // Lets try singleton in this also
    static Notifier *getNotifier(const int &_totalNotifications = 0);

    void restoreNotification(Notification *_notification);
    void notify(I_Product *_product, I_User *_user, I_Notification_Method *_method = nullptr) override;
    void notifyAll(I_Product *_product) override;
};