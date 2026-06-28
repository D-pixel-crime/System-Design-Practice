#pragma once
#include "../interfaces/I_Product.hpp"
#include "../interfaces/I_User.hpp"
#include "../interfaces/I_Notification_Method.hpp"
#include <tuple>

class Notification
{
private:
    I_Product *product = nullptr;
    I_User *subscriber = nullptr;
    I_Notification_Method *notificationMethod = nullptr;

public:
    ~Notification() {}
    Notification() = default;
    Notification(I_Product *_product, I_User *_subscriber, I_Notification_Method *_notificationMethod);

    void reset();
    void update(I_Product *_product, I_User *_subscriber, I_Notification_Method *_notificationMethod);
    std::tuple<I_Product *, I_User *, I_Notification_Method *> getNotificationDetails();
};