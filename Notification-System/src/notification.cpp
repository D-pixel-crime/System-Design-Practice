#include "../include/notification.hpp"

Notification::Notification(I_Product *_product, I_User *_subscriber, I_Notification_Method *_notificationMethod) : product(_product), subscriber(_subscriber), notificationMethod(_notificationMethod) {}

void Notification::update(I_Product *_product, I_User *_subscriber, I_Notification_Method *_notificationMethod)
{
    product = _product;
    subscriber = _subscriber;
    notificationMethod = _notificationMethod;
}

std::tuple<I_Product *, I_User *, I_Notification_Method *> Notification::getNotificationDetails()
{
    return std::make_tuple(product, subscriber, notificationMethod);
}