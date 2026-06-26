#pragma once
#include <string>

class I_Product
{
public:
    virtual ~I_Product() = default;

    virtual void updateCount() = 0;
    virtual int getAvailability() const = 0;
    virtual std::string getName() const = 0;
};