//
// Created by chi3hi on 11.01.22.
//

#pragma once

enum class err_t: int32_t
{
    SUCCESS,

    SOCKET_FAILED,
    SETSOCKOPT_FAILED,
    BIND_FAILED,
    LISTEN_FAILED,
    ACCEPTING_FAILED,
    READING_FAILED,
    WRITING_FAILED,
    OTHER_ERRORS
};

class Message;

class IConnection
{
public:
    explicit IConnection() = default;
    virtual ~IConnection() = default;

    virtual err_t TryAccept() = 0;

    virtual err_t Connect() = 0;
    virtual err_t Disconnect() = 0;
    virtual err_t Write(const Message&) = 0;
    virtual err_t Read(Message&) = 0;

    virtual bool IsConnected() const = 0;
};
