#include "../include/user.hpp"
#include <format>
#include <iostream>

NonVipUser::NonVipUser() : id(++total_users) {}

void NonVipUser::getStatus(I_Product *&_product) const
{
    auto res = _product->getAvailability();
    std::cout << (res ? std::format("Product {} is available!", _product->getName()) : std::format("Product {} is NOT available!", _product->getName())) << std::endl;
}