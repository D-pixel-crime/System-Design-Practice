#pragma once
#include "../interfaces/I_Notification_Method.hpp"
#include <iostream>
#include <format>

class Email_Notification_Method : public I_Notification_Method
{
public:
    void processNotification(I_Product *_product, I_User *_user) const override
    {
        std::cout << std::format("Product({}): User-{} notified through Email!", _product->getName(), _user->getId()) << std::endl;
    }
};

class Message_Notification_Method : public I_Notification_Method
{
public:
    void processNotification(I_Product *_product, I_User *_user) const override
    {
        std::cout << std::format("Product({}): User-{} notified through Message!", _product->getName(), _user->getId()) << std::endl;
    }
};

class Whatsapp_Notification_Method : public I_Notification_Method
{
public:
    void processNotification(I_Product *_product, I_User *_user) const override
    {
        std::cout << std::format("Product({}): User-{} notified through Whatsapp!", _product->getName(), _user->getId()) << std::endl;
    }
};

class Call_Notification_Method : public I_Notification_Method
{
public:
    void processNotification(I_Product *_product, I_User *_user) const override
    {
        std::cout << std::format("Product({}): User-{} notified through Call!", _product->getName(), _user->getId()) << std::endl;
    }
};