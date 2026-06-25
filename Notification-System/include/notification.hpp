#pragma once
#include "../interfaces/I_Product.hpp"
#include "../interfaces/I_User.hpp"
#include "../interfaces/I_Notification_Method.hpp"

class Notification
{
private:
    I_Product *product;
    I_User *subscriber;
    I_Notification_Method *notificationMethod;
};