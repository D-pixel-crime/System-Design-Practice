#include "../include/product.hpp"
#include "../include/notifier.hpp"

Product::Product(const std::string &_name) : name(_name), cnt(0) {}

void Product::updateCount(const int &_newCnt)
{
    cnt = _newCnt;

    Notifier::getNotifier()->notifyAll(this);
}

const int &Product::getAvailability() const
{
    return cnt;
}

const std::string &Product::getName() const
{
    return name;
}