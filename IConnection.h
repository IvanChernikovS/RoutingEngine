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
    CONNECTION_CLOSED = -7,
    WRITING_FAILED = -8,
    CLOSING_FAILED = -9,
};

class IConnection
{
public:
    explicit IConnection() = default;
    virtual ~IConnection() noexcept = default;

    virtual err_t Read(char*, size_t&) = 0;
    virtual err_t Write(const char*, size_t) = 0;
};
