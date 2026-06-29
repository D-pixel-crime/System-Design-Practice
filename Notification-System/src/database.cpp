#include "../include/database.hpp"
#include <mutex>

Database *Database::getConn()
{
    {
        std::lock_guard<std::mutex> lock(database_mutex);

        if (!db)
        {
            db = new Database();
        }
    }
    return db;
}

void Database::registerProduct(I_Product *_product)
{
    if (!products.count(_product))
    {
        products.insert(_product);
    }
}

void Database::registerUser(I_User *_user)
{
    if (!users.count(_user))
    {
        users.insert(_user);
    }
}

void Database::subscribeUser(I_Product *_product, I_User *_user, I_Notification_Method *_notificationMethod)
{
    registerProduct(_product);
    registerUser(_user);
    subscriptions[_product][_user].insert(_notificationMethod);
}

void Database::unsubscribeUser(I_Product *_product, I_User *_user, I_Notification_Method *_notificationMethod)
{
    subscriptions[_product][_user].erase(_notificationMethod);
}

const std::unordered_map<I_User *, std::set<I_Notification_Method *>> Database::getPreferences(I_Product *_product, I_User *_user)
{
    if (!_product || !products.count(_product))
    {
        return {};
    }
    if (!_user)
    {
        return subscriptions[_product];
    }
    return {{_user, subscriptions[_product][_user]}};
}