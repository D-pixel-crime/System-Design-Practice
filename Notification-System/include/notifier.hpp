#pragma once
#include "../interfaces/I_Notifier.hpp"
#include "notification.hpp"
#include <vector>

class Notifier : public I_Notifier
{
private:
    inline static Notifier *notifier = nullptr;
    static std::vector<Notification *> notificationPool;

    Notifier(int _totalNotifications);

public:
    // Try singleton in this also
    static Notifier *createNotificationPool(const int &_totalNotifications);

    void notify() override;
    void notifyAll(I_Product *_product) override;
};