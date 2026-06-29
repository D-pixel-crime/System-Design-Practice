#include "../include/messageQueue.hpp"
#include "../include/notifier.hpp"
#include <iostream>
#include <format>

Message_Queue::Message_Queue(const int &_size) : size(_size) {}

bool Message_Queue::hasReadyItem() const
{
    if (!retry_queue.empty() && retry_queue.front().deadline <= std::chrono::steady_clock::now())
    {
        return true;
    }
    if (!push_queue.empty())
    {
        return true;
    }
    return false;
}

void Message_Queue::pushNotification(Notification *_notification)
{
    {
        std::unique_lock<std::mutex> lock(size_mtx);

        size_cv.wait(lock, [this]()
                     { return push_queue.size() < size; });

        push_queue.push(_notification);
    }
    cv.notify_one();
}

void Message_Queue::pushFailed(RetryItem _item)
{
    if (_item.wait_duration == std::chrono::milliseconds(0))
    {
        _item.wait_duration = std::chrono::milliseconds(1);
    }
    else
    {
        _item.wait_duration *= 2;
    }

    if (_item.wait_duration > std::chrono::milliseconds(200))
    {
        Notifier *notifier = Notifier::getNotifier();

        auto [product, user, method] = _item.notification->getNotificationDetails();
        std::cout << std::format("Notification Failed for Product({}): User({}) through {} Notification!", product->getName(), user->getId(), method->getName()) << std::endl;

        notifier->restoreNotification(_item.notification);

        return;
    }

    _item.deadline += (_item.wait_duration + std::chrono::milliseconds(1));

    {
        std::unique_lock<std::mutex> lock(mtx);
        retry_queue.push(_item);
    }
    cv.notify_one();
}

RetryItem Message_Queue::popReadyItem()
{
    RetryItem ret{nullptr, std::chrono::steady_clock::now(), std::chrono::milliseconds(0)};

    if (!retry_queue.empty() && retry_queue.front().deadline <= std::chrono::steady_clock::now())
    {
        ret = retry_queue.front();
        retry_queue.pop();
    }
    else if (!push_queue.empty())
    {
        {
            std::unique_lock<std::mutex> lock(size_mtx);

            ret = {push_queue.front(), std::chrono::steady_clock::time_point(), std::chrono::milliseconds(0)};
            push_queue.pop();
        }
        size_cv.notify_one();
    }

    return ret;
}