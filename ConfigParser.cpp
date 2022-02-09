//
// Created by chi3hi on 27.01.22.
//

#include <fstream>
#include <iostream>

#include "ConfigParser.h"

ConfigParser::ConfigParser()
: mConfigData(std::make_shared<config_t>())
{}

ConfigParser::~ConfigParser() = default;

std::shared_ptr<config_t> ConfigParser::GetConfig() const
{
    return mConfigData;
}

bool ConfigParser::Parse(const char* pathToJason)
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

    if(!ParsePort() || !ParseIp() || !ParseMessageCapacity() || !ParseServerCapacity())
        return false;


    std::cout << "Config parsing completed" << std::endl;
    return true;
}

bool ConfigParser::ParsePort()
{
    mConfigData->port = mRoot["port"].asUInt();

    return mConfigData->isPortValid();
}

bool ConfigParser::ParseIp()
{
    mConfigData->ipAddress = mRoot["ip_address"].asString();

    return mConfigData->isIpValid();
}

bool ConfigParser::ParseMessageCapacity()
{
    mConfigData->messageCapacity = mRoot["message_capacity"].asUInt();

    return mConfigData->isMessageCapacityValid();
}

bool ConfigParser::ParseServerCapacity()
{
    mConfigData->serverCapacity = mRoot["server_capacity"].asUInt();

    return mConfigData->isServerCapacityValid();
}
