#include "../include/queueAllocator.hpp"
#include <mutex>

std::mutex queue_allocator_mutex;

Queue_Allocator::Queue_Allocator(int _totalQueues, const int &_queueSize)
{
    total_queues = _totalQueues;
    while (_totalQueues--)
    {
        queuePool.push_back(new Message_Queue(_queueSize));
    }
}

Queue_Allocator *Queue_Allocator::createQueuePool(const int &_totalQueues, const int &_queueSize)
{
    {
        std::lock_guard<std::mutex> lock(queue_allocator_mutex);

        if (!queueAllocator)
        {
            queueAllocator = new Queue_Allocator(_totalQueues, _queueSize);
        }
    }
    return queueAllocator;
}

Message_Queue *Queue_Allocator::allocate_queue()
{
    if (!queuePool.empty())
    {
        auto ret = queuePool.back();
        queuePool.pop_back();
        return ret;
    }
    return nullptr;
}

void Queue_Allocator::restore_queue(Message_Queue *_queue)
{
    if (queuePool.size() == total_queues)
    {
        return;
    }
    queuePool.push_back(_queue);
}