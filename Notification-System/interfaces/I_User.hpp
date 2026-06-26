#pragma once
#include <unordered_map>
#include <typeindex>
#include <vector>
#include "I_Notification_Method.hpp"
#include "I_Product.hpp"

class I_User
{
private:
    int id;

public:
    virtual ~I_User() = default;

    virtual void getStatus(I_Product *&_product) const = 0;

    virtual void addNotificationMethod(I_Product *&_product, I_Notification_Method *&_method) const = 0;
};