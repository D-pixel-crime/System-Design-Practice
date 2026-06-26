#pragma once
#include "../interfaces/I_Database.hpp"
#include "../interfaces/I_Product.hpp"
#include "../interfaces/I_User.hpp"
#include "../interfaces/I_Notification_Method.hpp"
#include <set>
#include <unordered_map>

class Database : public I_Database
{
private:
    std::set<I_Product *> products;
    std::set<I_User *> users;
    std::unordered_map<I_Product *, std::unordered_map<I_User *, std::set<I_Notification_Method *>>> subscriptions;

public:
    void registerProduct(I_Product *&_product) override;
    void registerUser(I_User *&_user) override;
    void subscribeUser(I_Product *&_product, I_User *&_user, I_Notification_Method *&_notificationMethod) override;
    void unsubscribeUser(I_Product *&_product, I_User *&_user, I_Notification_Method *&_notificationMethod) override;
    const std::unordered_map<I_User *, std::set<I_Notification_Method *>> getPreferences(I_Product *&_product, I_User *&_user) const override;
};