#include "../include/user.hpp"
#include "../include/database.hpp"
#include <format>
#include <iostream>

void NonVipUser::getStatus(I_Product *&_product) const
{
    auto res = _product->getAvailability();
    std::cout << (res ? std::format("Product {} is available!", _product->getName()) : std::format("Product {} is NOT available!", _product->getName())) << std::endl;
}

void NonVipUser::addNotificationMethod(I_Product *&_product, I_Notification_Method *&_method)
{
    Database *db = Database::getConn();
    db->subscribeUser(_product, this, _method);
}