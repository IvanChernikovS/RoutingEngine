//
// Created by chi3hi on 11.01.22.
//

#pragma once

enum class err_t: int32_t
{
    SUCCESS = 1,

    SOCKET_FAILED = -1,
    SETSOCKOPT_FAILED = -2,
    BIND_FAILED = -3,
    LISTEN_FAILED = -4,
    ACCEPTING_FAILED = -5,
    READING_FAILED = -6,
    WRITING_FAILED = -7,
    CLOSING_FAILED = -8,
};

class IConnection
{
public:
    explicit IConnection() = default;
    virtual ~IConnection() = default;

    virtual err_t TryAccept() = 0;

    virtual err_t Connect() = 0;
    virtual err_t Disconnect() = 0;
    virtual err_t Read(char*, size_t&) = 0;
    virtual err_t Write(const char*, size_t) = 0;

    virtual bool IsConnected() const = 0;
};
