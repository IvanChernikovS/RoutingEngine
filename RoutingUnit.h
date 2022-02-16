//
// Created by chi3hi on 09.02.22.
//

#pragma once

#include <memory>
#include <unordered_map>

#include "ThreadSafeQueue.h"
#include "MessageType.pb.h"

class ProxyConnection;

class RoutingUnit
{
public:
    explicit RoutingUnit(uint32_t maxPossibleClientsCount, size_t capacity);
    ~RoutingUnit() noexcept;

    void PollQueue();
    void PollChanel(int clientFd);

private:
    size_t mMessageCapacity = 0;
    size_t mMaxPossibleClientsCount = 0;
    ThreadSafeQueue<ipc::Package> mPackagesToSend;
    std::unordered_map<std::string, std::weak_ptr<ProxyConnection>> mConnections;

    void Broadcast(ipc::Package&);
    void Multicast(ipc::Package&);
    void Unicast(ipc::Package&);

    void RegisterClient(std::string userName, std::weak_ptr<ProxyConnection>);
    bool CheckForOverload() const;
    void CleanExpiredConnections();
};
