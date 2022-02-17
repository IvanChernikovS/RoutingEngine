//
// Created by chi3hi on 27.01.22.
//

#include <fstream>
#include <iostream>

#include "ConfigParser.h"
#include "Config.h"

ConfigParser::ConfigParser() = default;
ConfigParser::~ConfigParser() noexcept = default;

bool ConfigParser::Parse(const char* pathToJason, std::unique_ptr<config_t>& config)
{
    std::ifstream jsonConfig(pathToJason);
    if(!jsonConfig.is_open())
    {
        std::cout << "Json file hasn't opened. Path: " << pathToJason << std::endl;
        return false;
    }

    Json::Reader reader;
    if(!reader.parse(jsonConfig, mRoot, true))
    {
        std::cout << "Error parsing json: " << reader.getFormattedErrorMessages() << std::endl;
        return false;
    }

    if(mRoot.type() != Json::objectValue)
    {
        std::cout << "Error parsing config: root is not a object" << std::endl;
        return false;
    }

    if(!ParsePort(config) ||
       !ParseIp(config) ||
       !ParseMessageCapacity(config) ||
       !ParseServerCapacity(config))
        return false;

    std::cout << "Config parsing completed" << std::endl;
    return true;
}

bool ConfigParser::ParsePort(std::unique_ptr<config_t>& config)
{
    config->port = mRoot["port"].asUInt();

    return config->isPortValid();
}

bool ConfigParser::ParseIp(std::unique_ptr<config_t>& config)
{
    config->ipAddress = mRoot["ip_address"].asString();

    return config->isIpValid();
}

bool ConfigParser::ParseMessageCapacity(std::unique_ptr<config_t>& config)
{
    config->messageCapacity = mRoot["message_capacity"].asUInt();

    return config->isMessageCapacityValid();
}

bool ConfigParser::ParseServerCapacity(std::unique_ptr<config_t>& config)
{
    config->serverCapacity = mRoot["server_capacity"].asUInt();

    return config->isServerCapacityValid();
}
