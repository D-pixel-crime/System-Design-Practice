#pragma once
#include "notification.hpp"
#include <queue>
#include <chrono>
#include <mutex>
#include <condition_variable>

struct RetryItem
{
    Notification *notification;
    std::chrono::steady_clock::time_point deadline;
    std::chrono::milliseconds wait_duration;
};

class Message_Queue
{
private:
    int size;
    std::queue<Notification *> push_queue;
    std::queue<RetryItem> retry_queue;

public:
    std::mutex mtx;
    std::condition_variable cv;
    std::mutex size_mtx;
    std::condition_variable size_cv;

    Message_Queue(const int &_size);

    const int getCurrSize() const
    {
        return push_queue.size();
    }

    bool hasReadyItem() const;
    void pushNotification(Notification *_notification);
    void pushFailed(RetryItem _item);
    RetryItem popReadyItem();
};