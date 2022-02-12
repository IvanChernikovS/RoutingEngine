//
// Created by chi3hi on 27.01.22.
//

#pragma once

#include <memory>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

struct config_t;

class ConfigParser
{
public:
    explicit ConfigParser();
    virtual ~ConfigParser();

    virtual bool Parse(const char* path, std::unique_ptr<config_t>& config);

private:
    bool ParsePort(std::unique_ptr<config_t>&);
    bool ParseIp(std::unique_ptr<config_t>&);
    bool ParseMessageCapacity(std::unique_ptr<config_t>&);
    bool ParseServerCapacity(std::unique_ptr<config_t>&);

    Json::Value mRoot;
};