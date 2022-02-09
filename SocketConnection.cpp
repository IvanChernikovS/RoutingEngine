//
// Created by chi3hi on 11.01.22.
//

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

#include "SocketConnection.h"

SocketConnection::SocketConnection(int clientSocketFd)
: mClientSocketFd(clientSocketFd)
{}

SocketConnection::~SocketConnection() noexcept
{
    if(IsConnected())
        close(mClientSocketFd);
}

err_t SocketConnection::Read(char* message, size_t& length)
{
    size_t actualBytes = recv(mClientSocketFd, message, length, 0);

    if(actualBytes > length || actualBytes < 0)
    {
        std::cout << "Reading failed" << std::endl;
        return err_t::READING_FAILED;
    }
    if(actualBytes == 0)
    {
        std::cout << "Connection closed" << std::endl;
        return err_t::CONNECTION_CLOSED;
    }

    length = actualBytes;

    return err_t::SUCCESS;
}

err_t SocketConnection::Write(const char* message, size_t size)
{
    if(send(mClientSocketFd, message, size, 0 ) < size)
    {
        std::cout << "Writing failed" << std::endl;
        return err_t::WRITING_FAILED;
    }

    return err_t::SUCCESS;
}

void SocketConnection::Disconnect()
{
    close(mClientSocketFd);
}

bool SocketConnection::IsConnected() const
{
    return mClientSocketFd > 0;
}