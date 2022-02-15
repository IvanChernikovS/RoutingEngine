//
// Created by chi3hi on 09.02.22.
//

#pragma once

#include <iostream>
#include <mutex>
#include <queue>
#include <chrono>
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

    bool WaitAndPop(T& value)
    {
        std::unique_lock<std::mutex> ul(mMutex);
        auto pred = [self = this]{ return !self->mDataQueue.empty(); };

        if(!mCV.wait_for(ul, std::chrono::minutes(2), pred))
        {
            std::cout << "Waiting on queue timed out" << std::endl;
            return false;
        }
        value = mDataQueue.front();
        mDataQueue.pop();
        return true;
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
