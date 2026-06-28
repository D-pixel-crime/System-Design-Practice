#pragma once
#include "../interfaces/I_User.hpp"
#include "../interfaces/I_Product.hpp"

class NonVipUser : public I_User
{
public:
    void getStatus(I_Product *&_product) const override;
    void addNotificationMethod(I_Product *&_product, I_Notification_Method *&_method) override;
};