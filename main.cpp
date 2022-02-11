#include <iostream>
#include <memory>
#include <future>
#include <mutex>
#include <vector>

#include "Server.h"
#include "ConfigParser.h"
#include "RoutingUnit.h"

int main(const int argc, const char** argv)
{
    ConfigParser configParser;
    if(argc <= 1 && !argv[1])
    {
        std::cout << "Should be path to jason as program arguments" << std::endl;
        return -1;
    }
    if(!configParser.Parse(argv[1]))
    {
        std::cout << "Invalid parsing" << std::endl;
        return -1;
    }

    uint32_t maxPossibleClientsCount = configParser.GetConfig()->serverCapacity;

    auto server = std::make_unique<Server>(configParser.GetConfig()->ipAddress,
                                           configParser.GetConfig()->port,
                                           maxPossibleClientsCount);

    if(!server->Connect())
        return -1;

    auto routingUnit = std::make_shared<RoutingUnit>(maxPossibleClientsCount);

    routingUnit->PollQueue();

    auto connectionHandler = [capacity = configParser.GetConfig()->messageCapacity,
                              routingUnit](int clientFd){

        if(clientFd <= 0)
            return -1;

        routingUnit->PollChanel(clientFd, capacity);

        return 0;
    };

    std::vector<std::future<int>> threadsPull;
    threadsPull.reserve(maxPossibleClientsCount);

    while(true)
    {
        if(server->Select() <= 0)
            break;

        auto future = std::async(std::launch::async, connectionHandler, server->TryAccept());
        threadsPull.emplace_back(std::move(future));
    }

    while(!threadsPull.empty())
    {
        for(auto it = threadsPull.begin(); it != threadsPull.end(); )
        {
            if(it->wait_for(std::chrono::seconds(5)) == std::future_status::timeout)
            {
                it++;
                continue;
            }

            std::cout << "Return code from future: " << it->get() << std::endl;
            it = threadsPull.erase(it);
        }
    }

    return 0;
}
