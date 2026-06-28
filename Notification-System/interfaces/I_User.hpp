#pragma once
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <atomic>
#include "I_Notification_Method.hpp"
#include "I_Product.hpp"

class I_User
{
private:
    inline static std::atomic<int> total_users = 0;
    int id;

public:
    I_User() : id(++total_users) {}
    virtual ~I_User() = default;

    const int getId() const
    {
        return id;
    }

    virtual void getStatus(I_Product *&_product) const = 0;
    virtual void addNotificationMethod(I_Product *&_product, I_Notification_Method *&_method) = 0;
};