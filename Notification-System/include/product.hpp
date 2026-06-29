#pragma once
#include "../interfaces/I_Product.hpp"
#include <string>

class Product : public I_Product
{
private:
    std::string name;
    int cnt;

public:
    Product(const std::string &_name);

    void updateCount(const int &_newCnt) override;
    const int &getAvailability() const override;
    const std::string &getName() const override;
};