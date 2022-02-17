//
// Created by chi3hi on 04.02.22.
//

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>

#include "Server.h"

Server::Server(const std::string& ipAddress, uint32_t port, uint32_t capacity)
: mMaxClientCount(capacity)
, mTimeout({5 * 60, 0})
, mSocketAddress({AF_INET, htons(port)})
{
    if(inet_pton(AF_INET, ipAddress.data(), &mSocketAddress.sin_addr) <= 0)
    {
        std::cout << "Invalid ip address" << std::endl;
    }

    mSocketClientFds.reserve(mMaxClientCount);
}

Server::~Server() noexcept
{
    DisconnectClients();

    if(IsConnected())
        close(mServerSocketFd);
}

bool Server::Connect()
{
    if((mServerSocketFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << "Socket failed" << std::endl;
        return false;
    }
    std::cout << "Socket created" << std::endl;

    int opt = 1;
    if(setsockopt(mServerSocketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cout << "Setsockopt failed" << std::endl;
        close(mServerSocketFd);
        return false;
    }

    if(bind(mServerSocketFd, (struct sockaddr*)&mSocketAddress, sizeof(mSocketAddress)) < 0)
    {
        std::cout << "Bind failed" << std::endl;
        close(mServerSocketFd);
        return false;
    }
    std::cout << "Socket bound" << std::endl;

    if(listen(mServerSocketFd, static_cast<int>(mMaxClientCount)) < 0)
    {
        std::cout << "Listen failed" << std::endl;
        close(mServerSocketFd);
        return false;
    }
    std::cout << "Socket listened" << std::endl;

    if(ioctl(mServerSocketFd, FIONBIO, &opt) < 0)
    {
        std::cout << "Ioctl failed" << std::endl;
        close(mServerSocketFd);
        return false;
    }
    std::cout << "Ioctl set" << std::endl;

    return true;
}

void Server::DisconnectClients()
{
    for(const auto& fd: mSocketClientFds)
        close(fd);
}

bool Server::IsConnected() const
{
    return mServerSocketFd > 0;
}

int Server::Select()
{
    FD_ZERO(&mWorking_set);
    mLargest_socket = mServerSocketFd;
    FD_SET(mServerSocketFd, &mWorking_set);

    std::cout << "Waiting on select..." << std::endl;
    int rc = select(mLargest_socket + 1, &mWorking_set, nullptr, nullptr, &mTimeout);

    if(rc < 0)
    {
        std::cout << "Selection failed" << std::endl;
        return rc;
    }
    if(rc == 0)
    {
        std::cout << "Selection timed out" << std::endl;
        return rc;
    }
    if(!FD_ISSET(mServerSocketFd, &mWorking_set))
    {
        std::cout << "Descriptor: " << mServerSocketFd << " is not ready" << std::endl;
        return -1;
    }

    return rc;
}

int Server::TryAccept()
{
    int mSocketLen = sizeof(mSocketAddress);
    int clientSocketFd = accept(mServerSocketFd,(struct sockaddr*)&mSocketAddress, (socklen_t*)&mSocketLen);

    if(clientSocketFd < 0)
    {
        std::cout << "Socket not accepted" << std::endl;

        if(errno != EWOULDBLOCK)
            std::cout << "Socket not accepted because of EWOULDBLOCK" << std::endl;

        return clientSocketFd;
    }

    FD_SET(clientSocketFd, &mWorking_set);
    if(clientSocketFd > mLargest_socket)
        mLargest_socket = clientSocketFd;

    mSocketClientFds.emplace_back(clientSocketFd);

    std::cout << "Socket accepted" << std::endl;

    return clientSocketFd;
}