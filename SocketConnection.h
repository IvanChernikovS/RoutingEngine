//
// Created by chi3hi on 11.01.22.
//

#pragma once

#include <netinet/in.h>

#include "IConnection.h"

class Message;

class SocketConnection: public IConnection
{
public:
    explicit SocketConnection(const std::string& socketAddr, uint32_t socketPort);
    ~SocketConnection() override = default;

    err_t TryAccept() override;

    err_t Connect() override;
    err_t Disconnect() override;
    err_t Write(const Message& message) override;
    err_t Read(Message& message) override;

    bool IsConnected() const override;

private:
    int mServerSocketFd = 0;
    int mClientSocketFd = 0;
    struct sockaddr_in mSocketAddr{};
};

