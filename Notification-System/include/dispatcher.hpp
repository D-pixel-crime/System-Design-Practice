#pragma once
#include "notification.hpp"

class Dispatcher
{
public:
    void push(Notification *&_notification) const;
};