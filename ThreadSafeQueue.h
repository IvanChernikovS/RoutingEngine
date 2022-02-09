//
// Created by chi3hi on 09.02.22.
//

#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>

template<class T>
class ThreadSafeQueue
{
public:
    explicit ThreadSafeQueue() = default;
    ~ThreadSafeQueue() noexcept = default;

    void Push(T value)
    {
        std::lock_guard<std::mutex> lg(mMutex);
        mDataQueue.push(std::move(value));
        mCV.notify_one();
    }
    void WaitAndPop(T& value)
    {
        std::unique_lock<std::mutex> ul(mMutex);
        mCV.wait(ul, [this]{ return !mDataQueue.empty(); });
        value = mDataQueue.front();
        mDataQueue.pop();
    }
    bool Empty() const
    {
        std::lock_guard<std::mutex> lg(mMutex);
        return mDataQueue.empty();
    }
private:
    mutable std::mutex mMutex;
    std::queue<T> mDataQueue;
    std::condition_variable mCV;
};
