#pragma once
#include <string>

class I_Product;
class I_User;

class I_Notification_Method
{
private:
    std::string name;

public:
    virtual ~I_Notification_Method() = default;
    I_Notification_Method(const std::string &_name) : name(_name) {}

    const std::string &getName() const
    {
        return name;
    }

    virtual void processNotification(I_Product *_product, I_User *_user) const = 0;
};