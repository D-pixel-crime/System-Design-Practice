#pragma once
#include "../interfaces/I_Product.hpp"
#include <string>

class Product : public I_Product
{
private:
    std::string name;
    int cnt;

public:
    void updateCount() override;
    int getAvailability() const override;
    std::string getName() const override;
};