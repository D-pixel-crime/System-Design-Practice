#pragma once
#include <string>

class I_Product
{
public:
    virtual ~I_Product() = default;

    virtual void updateCount(const int &_newCnt) = 0;
    virtual const int &getAvailability() const = 0;
    virtual const std::string &getName() const = 0;
};