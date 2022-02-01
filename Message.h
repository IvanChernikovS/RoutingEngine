//
// Created by chi3hi on 26.01.22.
//

#pragma once

#include <cstdio>
#include <cstring>

class Message
{
public:
    explicit Message(size_t capacity);
    ~Message() noexcept;

    Message(const Message& message) = delete;
    Message(Message&& message) = delete;

    Message& operator=(const Message& message) = delete;
    Message& operator=(Message&& message) = delete;

    char* Payload() { return mPayload; }
    const char* Payload() const { return mPayload; }

    void SetSize(size_t size) { mSize = size; }
    size_t GetSize() const { return mSize; }

    size_t GetCapacity() const { return mCapacity; }

private:
    char* mPayload = nullptr;
    size_t mCapacity = 0;
    size_t mSize = 0;
};
