//
// Created by chi3hi on 26.01.22.
//

#pragma once

#include <string>
#include <sstream>

struct config_t
{
    uint32_t port = 0;
    uint32_t messageCapacity = 0;
    uint32_t serverCapacity = 0;
    std::string ipAddress = "0.0.0.0";

    bool isPortValid() const
    {
        auto portSize = std::to_string(port).size();
        return portSize > 0 && portSize < 6;
    }

    bool isMessageCapacityValid() const
    {
        return messageCapacity % 128 == 0;
    }

    bool isServerCapacityValid() const
    {
        return serverCapacity < 1024; //due to select() function
    }

    bool isIpValid() const
    {
        std::string tempStr;
        std::stringstream ss(ipAddress);

        for(auto i = 0; ss >> i;)
        {
            if(i < 0 || i > 255)
                return false;

            tempStr += std::to_string(i);

            if(ss.peek() == '.')
                ss.ignore();
        }

        if(ipAddress.size() - 3 != tempStr.size())
            return false;

        return true;
    }
};