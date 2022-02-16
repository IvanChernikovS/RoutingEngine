//
// Created by chi3hi on 03.02.22.
//

#pragma once

#include "MessageType.pb.h"

class IConnection;
enum class err_t;

class ProxyConnection
{
public:
    explicit ProxyConnection(size_t capacity, int clientFd);
    ~ProxyConnection() noexcept;

    err_t Read(ipc::Package&);
    err_t Write(ipc::Package&);

private:
    size_t mMessageCapacity = 0;
    std::unique_ptr<IConnection> mConnection;
};
