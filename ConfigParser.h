//
// Created by chi3hi on 27.01.22.
//

#pragma once

#include <memory>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

#include "Config.h"

class ConfigParser
{
public:
    explicit ConfigParser();
    ~ConfigParser();

    bool Parse(const char* path);
    std::shared_ptr<config_t> GetConfig() const;

private:
    bool ParsePort();
    bool ParseIp();
    bool ParseCapacity();

    std::shared_ptr<config_t> mConfigData;
    Json::Value mRoot;
};