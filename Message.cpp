//
// Created by chi3hi on 26.01.22.
//

#include "Message.h"

Message::Message(size_t capacity)
: mCapacity(capacity)
{
    if(mCapacity > 0)
        mPayload = new char[mCapacity];
}

Message::~Message() noexcept
{
    delete[] mPayload;
}