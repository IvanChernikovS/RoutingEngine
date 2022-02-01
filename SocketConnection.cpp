//
// Created by chi3hi on 11.01.22.
//

#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include "SocketConnection.h"
#include "Message.h"

SocketConnection::SocketConnection(const std::string& socketAddr, uint32_t socketPort)
{
    mSocketAddr.sin_family = AF_INET;
    mSocketAddr.sin_port = htons(socketPort);

    if(inet_pton(AF_INET, socketAddr.c_str(), &mSocketAddr.sin_addr) <= 0)
    {
        std::cout << "Invalid address" << std::endl;
    }
}

err_t SocketConnection::TryAccept()
{
    int mSocketLen = sizeof(mSocketAddr);
    mClientSocketFd = accept(mServerSocketFd,(struct sockaddr*)&mSocketAddr, (socklen_t*)&mSocketLen);

    if(mClientSocketFd <= 0)
    {
        std::cout << "Socket not accepted" << std::endl;
        return err_t::ACCEPTING_FAILED;
    }

    std::cout << "Socket accepted" << std::endl;

    return err_t::SUCCESS;
}

err_t SocketConnection::Connect()
{
    int opt = 1;

    if((mServerSocketFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cout << "Socket failed" << std::endl;
        return err_t::SOCKET_FAILED;
    }
    std::cout << "Socket created" << std::endl;

    if(setsockopt(mServerSocketFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cout << "Setsockopt failed" << std::endl;
        return err_t::SETSOCKOPT_FAILED;
    }

    if(bind(mServerSocketFd, (struct sockaddr*)&mSocketAddr, sizeof(mSocketAddr)) < 0)
    {
        std::cout << "Bind failed" << std::endl;
        return err_t::BIND_FAILED;
    }
    std::cout << "Socket binded" << std::endl;

    if(listen(mServerSocketFd, 5) < 0)
    {
        std::cout << "Listen failed" << std::endl;
        return err_t::LISTEN_FAILED;
    }
    std::cout << "Socket heard" << std::endl;

    //fcntl(mServerSocketFd, F_SETFL, O_NONBLOCK);

    return err_t::SUCCESS;
}

err_t SocketConnection::Disconnect()
{
    close(mServerSocketFd);
    close(mClientSocketFd);

    return err_t::SUCCESS;
}

err_t SocketConnection::Read(Message& message)
{
    if(recv(mClientSocketFd, message.Payload(), message.GetCapacity(), 0) <= 0)
    {
        std::cout << "Reading failed" << std::endl;
        return err_t::READING_FAILED;
    }

    message.SetSize(strlen(message.Payload()));

    std::cout << "Message: " << message.Payload() << std::endl;

    return err_t::SUCCESS;
}

err_t SocketConnection::Write(const Message& message)
{
    send(mClientSocketFd, message.Payload(), message.GetSize(), 0 );
    std::cout << "Message: " << message.Payload() << "; has been sent." << std::endl;

    return err_t::SUCCESS;
}

bool SocketConnection::IsConnected() const
{
    return mClientSocketFd > 0;
}