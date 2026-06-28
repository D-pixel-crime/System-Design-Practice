#pragma once
#include "notification.hpp"
#include "messageQueue.hpp"

class Dispatcher
{
private:
    Message_Queue *queue;

public:
    Dispatcher(Message_Queue *_queue);

    void pullNotification();
    void deployNotification(Notification *_notification) const;
};