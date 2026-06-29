#pragma once
#include "../interfaces/I_Notification_Method.hpp"
#include "../interfaces/I_Product.hpp"
#include "../interfaces/I_User.hpp"
#include <iostream>
#include <format>
#include <syncstream>

class Email_Notification_Method : public I_Notification_Method
{
public:
  Email_Notification_Method() : I_Notification_Method("Email") {}

  void processNotification(I_Product *_product, I_User *_user) const override
  {
    std::osyncstream(std::cout) << std::format("Product({}): User-{} notified through Email!\n",
                                               _product->getName(), _user->getId());
  }
};

class Message_Notification_Method : public I_Notification_Method
{
public:
  Message_Notification_Method() : I_Notification_Method("Message") {}

  void processNotification(I_Product *_product, I_User *_user) const override
  {
    std::osyncstream(std::cout) << std::format("Product({}): User-{} notified through Message!\n",
                                               _product->getName(), _user->getId());
  }
};

class Whatsapp_Notification_Method : public I_Notification_Method
{
public:
  Whatsapp_Notification_Method() : I_Notification_Method("Whatsapp") {}

  void processNotification(I_Product *_product, I_User *_user) const override
  {
    std::osyncstream(std::cout) << std::format("Product({}): User-{} notified through Whatsapp!\n",
                                               _product->getName(), _user->getId());
  }
};

class Call_Notification_Method : public I_Notification_Method
{
public:
  Call_Notification_Method() : I_Notification_Method("Call") {}

  void processNotification(I_Product *_product, I_User *_user) const override
  {
    std::osyncstream(std::cout) << std::format("Product({}): User-{} notified through Call!\n",
                                               _product->getName(), _user->getId());
  }
};