#pragma once

class I_Notification_Method
{
public:
    virtual ~I_Notification_Method() = default;

    virtual void processNotification() = 0;
};