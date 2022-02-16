//
// Created by chi3hi on 09.02.22.
//

#include <thread>
#include <chrono>
#include <algorithm>
#include <unordered_set>

#include "IConnection.h"
#include "RoutingUnit.h"
#include "ProxyConnection.h"

std::mutex mutex;

RoutingUnit::RoutingUnit(uint32_t maxPossibleClientsCount, size_t capacity)
: mMessageCapacity(capacity)
, mMaxPossibleClientsCount(maxPossibleClientsCount)
{}

RoutingUnit::~RoutingUnit() noexcept = default;

void RoutingUnit::PollQueue()
{
    auto pollingHandler = [self = this]{
        ipc::Package package;

        while(true)
        {
            if(!self->mPackagesToSend.WaitAndPop(package))
                break;

            int receiversCount = package.header().receiver_size();
            if(receiversCount > 1)
                self->Multicast(package);
            else if(receiversCount == 1)
                self->Unicast(package);
        }
    };

    std::thread tPolling(pollingHandler);
    if(tPolling.joinable())
        tPolling.detach();
}

void RoutingUnit::PollChanel(int clientFd)
{
    ipc::Package package;
    auto proxyConnection = std::make_shared<ProxyConnection>(mMessageCapacity, clientFd);

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        auto result = proxyConnection->Read(package);
        if(result == err_t::READING_FAILED)
            continue;
        if(result == err_t::CONNECTION_CLOSED)
            break;

        if(package.header().messagetype() == ipc::REGISTRATION)
        {
            RegisterClient(package.header().sender().sender(),
                           std::weak_ptr<ProxyConnection>(proxyConnection));
            std::cout << package.header().sender().sender() << " - registered." << std::endl;
            continue;
        }
        else if(package.header().messagetype() == ipc::MESSAGE)
        {
            std::cout << "Message: " << package.payload().value()
                      << " -> from:" << package.header().sender().sender() << std::endl;

            mPackagesToSend.Push(package);
        }
    }
}

void RoutingUnit::Broadcast(ipc::Package& package)
{
    std::string sender = package.header().sender().sender();

    for(auto& connection: mConnections)
    {
        if(connection.second.expired() || connection.first == sender)
            continue;

        connection.second.lock()->Write(package);
    }
}

void RoutingUnit::Multicast(ipc::Package& package)
{
    std::unordered_set<std::string> receivers;
    int receiversCount = package.header().receiver_size();

    for(auto i = 0; i < receiversCount; ++i)
        receivers.emplace(package.header().receiver()[i].receiver());

    for(auto& receiver: receivers)
    {
        auto desiredReceiver = mConnections.find(receiver);

        if(desiredReceiver == mConnections.cend() || desiredReceiver->second.expired())
            continue;

        desiredReceiver->second.lock()->Write(package);
    }
}

void RoutingUnit::Unicast(ipc::Package &package)
{
    std::string receiver = package.header().receiver().cbegin()->receiver();

    auto desiredReceiver = mConnections.find(receiver);

    if(desiredReceiver == mConnections.cend())
        return;

    if(!desiredReceiver->second.expired())
        desiredReceiver->second.lock()->Write(package);
}

void RoutingUnit::RegisterClient(std::string userName, std::weak_ptr<ProxyConnection> connectionWeak)
{
    std::lock_guard<std::mutex> lg(mutex);

    if(CheckForOverload())
        CleanExpiredConnections();

    mConnections.emplace(std::move(userName),std::move(connectionWeak));
}

bool RoutingUnit::CheckForOverload() const
{
    int delta = 5;
    return mConnections.size() > mMaxPossibleClientsCount - delta;
}

void RoutingUnit::CleanExpiredConnections()
{
    std::lock_guard<std::mutex> lg(mutex);

    for(auto it = mConnections.begin(); it != mConnections.end();)
        it->second.expired() ? it = mConnections.erase(it) : ++it;
}