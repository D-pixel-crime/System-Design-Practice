#pragma once
#include "I_Product.hpp"

class I_Notifier
{
public:
    virtual ~I_Notifier() = default;

    virtual void notify() = 0;

    virtual void notifyAll(I_Product *_product) = 0;
};