#pragma once
#include <queue>
#include "notification.hpp"

class Message_Queue
{
private:
    int size;
    std::queue<Notification *> push_queue;
    std::queue<Notification *> retry_queue;

public:
    bool scheduleNotification(const Notification *&_notification);
};