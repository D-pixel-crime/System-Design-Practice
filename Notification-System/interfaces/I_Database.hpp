#pragma once
#include "I_Product.hpp"
#include "I_User.hpp"
#include "I_Notification_Method.hpp"
#include <set>
#include <unordered_map>

class I_Database
{
private:
    std::set<I_Product *> products;
    std::set<I_User *> users;
    std::unordered_map<I_Product *, std::unordered_map<I_User *, std::set<I_Notification_Method *>>> subscriptions;

public:
    virtual ~I_Database() = default;

    virtual void registerProduct(I_Product *&_product) = 0;

    virtual void registerUser(I_User *&_user) = 0;

    virtual void subscribeUser(I_Product *&_product, I_User *&_user, I_Notification_Method *&_notificationMethod) = 0;

    virtual void unsubscribeUser(I_Product *&_product, I_User *&_user, I_Notification_Method *&_notificationMethod) = 0;

    virtual const std::unordered_map<I_User *, std::set<I_Notification_Method *>> getPreferences(I_Product *&_product, I_User *&_user) const = 0;
};