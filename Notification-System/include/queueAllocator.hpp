#pragma once
#include "messageQueue.hpp"
#include <queue>
#include <vector>
#include <mutex>

class Queue_Allocator
{
private:
    struct Comp
    {
        bool operator()(Message_Queue *a, Message_Queue *b)
        {
            return a->getCurrSize() > b->getCurrSize();
        }
    };

    inline static std::mutex allocator_mtx;
    inline static int total_queues = 0;
    inline static Queue_Allocator *queueAllocator = nullptr;
    inline static std::priority_queue<Message_Queue *, std::vector<Message_Queue *>, Comp> queuePool;

    Queue_Allocator(int _totalQueues, const int &_queueSize);

public: // Try singleton in this
    static Queue_Allocator *createQueuePool(const int &_totalQueues, const int &_queueSize);

    static Message_Queue *allocate_queue();
};