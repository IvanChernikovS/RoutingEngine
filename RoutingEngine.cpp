//
// Created by chi3hi on 11.02.22.
//

#include "RoutingEngine.h"

#include "RoutingUnit.h"
#include "Server.h"
#include "Config.h"

RoutingEngine::RoutingEngine(std::unique_ptr<config_t>& config)
: mRoutingUnit(std::make_unique<RoutingUnit>(config->serverCapacity, config->messageCapacity))
, mServer(std::make_unique<Server>(config->ipAddress, config->port, config->serverCapacity))
{
    threadsPull.reserve(config->serverCapacity);
}

RoutingEngine::~RoutingEngine() noexcept = default;

void RoutingEngine::Run()
{
    if(!mServer->Connect())
        return;

    mRoutingUnit->PollQueue();

    auto connectionHandler = [this](int clientFd){

        if(clientFd <= 0)
            return -1;

        mRoutingUnit->PollChanel(clientFd);

        return 0;
    };

    while(true)
    {
        if(mServer->Select() <= 0)
            break;

        auto future = std::async(std::launch::async, connectionHandler, mServer->TryAccept());
        threadsPull.emplace_back(std::move(future));
    }
}

void RoutingEngine::WaitAndStop()
{
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
}