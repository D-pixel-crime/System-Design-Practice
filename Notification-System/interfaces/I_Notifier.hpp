#pragma once
#include "I_Product.hpp"
#include "I_User.hpp"
#include "I_Notification_Method.hpp"

class I_Notifier
{
public:
    virtual ~I_Notifier() = default;

    virtual void notify(I_Product *_product, I_User *_user, I_Notification_Method *_method) = 0;
    virtual void notifyAll(I_Product *_product) = 0;
};