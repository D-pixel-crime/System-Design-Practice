#pragma once
#include <unordered_map>
#include <typeindex>
#include <vector>
#include "I_Notification_Method.hpp"
#include "I_Product.hpp"

class I_User
{
private:
    std::unordered_map<std::type_index, std::vector<I_Notification_Method *>> subscribedProducts;

public:
    virtual ~I_User() = default;

    virtual void getStatus(I_Product *&_product) const = 0;
};