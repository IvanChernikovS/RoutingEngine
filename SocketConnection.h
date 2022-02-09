//
// Created by chi3hi on 11.01.22.
//

#pragma once

#include "IConnection.h"

class SocketConnection : public IConnection
{
public:
    explicit SocketConnection(int clientSocketFd);
    ~SocketConnection() noexcept override;

    err_t Read(char*, size_t&) override;
    err_t Write(const char*, size_t) override;

    void Disconnect();
    bool IsConnected() const;

private:
    int mClientSocketFd = 0;
};

