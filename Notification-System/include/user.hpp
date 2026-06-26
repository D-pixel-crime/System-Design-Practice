#pragma once
#include "../interfaces/I_User.hpp"
#include "../interfaces/I_Product.hpp"
#include <atomic>

class NonVipUser : public I_User
{
private:
    inline static std::atomic<int> total_users = 0;
    int id = 0;

public:
    NonVipUser();

    void getStatus(I_Product *&_product) const override;
    void addNotificationMethod(I_Product *&_product, I_Notification_Method *&_method) const override;
};