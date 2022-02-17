//
// Created by chi3hi on 04.02.22.
//

#pragma once

#include <netinet/in.h>
#include <sys/poll.h>
#include <string>
#include <vector>

#include "IConnection.h"

class Server
{
public:
    explicit Server(const std::string& ipAddress, uint32_t port, uint32_t capacity);
    ~Server() noexcept;

    bool Connect();
    void DisconnectClients();
    bool IsConnected() const;

    int Select();
    int TryAccept();

private:
    uint32_t mMaxClientCount = 0;
    int mServerSocketFd = 0;
    int mLargest_socket = 0;
    fd_set mWorking_set{};
    struct timeval mTimeout{};
    struct sockaddr_in mSocketAddress{};
    std::vector<int> mSocketClientFds;
};
