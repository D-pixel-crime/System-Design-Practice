#pragma once
#include "messageQueue.hpp"
#include <set>

class Queue_Allocator
{
private:
    static int total_queues;
    std::set<Message_Queue *> pool;

public:
    Message_Queue *allocate_queue();

    void restore_queue(Message_Queue *_queue);
};