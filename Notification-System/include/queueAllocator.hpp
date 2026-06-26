#pragma once
#include "messageQueue.hpp"
#include <vector>

class Queue_Allocator
{
private:
    inline static int total_queues = 0;
    inline static Queue_Allocator *queueAllocator = nullptr;
    static std::vector<Message_Queue *> queuePool;

    Queue_Allocator(int _totalQueues, const int &_queueSize);

public:
    // Try singleton in this
    static Queue_Allocator *createQueuePool(const int &_totalQueues, const int &_queueSize);

    Message_Queue *allocate_queue();
    void restore_queue(Message_Queue *_queue);
};