//
// Created by chi3hi on 03.02.22.
//

#include "ProxyConnection.h"
#include "SocketConnection.h"
#include "MessageType.pb.cc"

ProxyConnection::ProxyConnection(size_t capacity, int clientFd)
: mMessageCapacity(capacity)
, mConnection(std::make_unique<SocketConnection>(clientFd))
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

ProxyConnection::~ProxyConnection() noexcept
{
    google::protobuf::ShutdownProtobufLibrary();
}

err_t ProxyConnection::Read(ipc::Package& package)
{
    size_t length = mMessageCapacity;
    char* buffer = new char[mMessageCapacity];

    auto result = mConnection->Read(buffer, length);
    if(result == err_t::READING_FAILED || result == err_t::CONNECTION_CLOSED)
    {
        delete[] buffer;
        return result;
    }

    package.Clear();
    package.ParseFromArray(buffer, static_cast<int>(length));

    delete[] buffer;
    return result;
}

err_t ProxyConnection::Write(ipc::Package& package)
{
    size_t actualSize = package.ByteSizeLong();
    char* buffer = new char[actualSize];

    package.SerializeToArray(buffer, static_cast<int>(actualSize));

    auto result = mConnection->Write(buffer, actualSize);

    delete[] buffer;
    return result;
}