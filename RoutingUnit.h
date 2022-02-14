//
// Created by chi3hi on 09.02.22.
//

#pragma once

#include <memory>
#include <unordered_map>

#include "ThreadSafeQueue.h"
#include "MessageType.pb.h"

class IConnection;

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
    std::unordered_map<std::string, std::weak_ptr<IConnection>> mConnections;
    ThreadSafeQueue<ipc::Package> mPackagesToSend;

    decltype(auto) FindDesireReceiver(const std::string& receiver);
    bool CheckForOverload() const;
    void CleanExpiredConnections();

    void Broadcast(ipc::Package&);
    void Multicast(ipc::Package&);
    void Unicast(ipc::Package&);

    void RegisterClient(std::string userName, std::weak_ptr<IConnection>);
};
