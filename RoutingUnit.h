//
// Created by chi3hi on 09.02.22.
//

#pragma once

#include <memory>
#include <vector>

#include "ThreadSafeQueue.h"
#include "MessageType.pb.h"

class IConnection;

class RoutingUnit
{
public:
    explicit RoutingUnit(uint32_t maxPossibleClientsCount);
    ~RoutingUnit() noexcept;

    void PollQueue();
    void PollChanel(int clientFd, size_t capacity);

private:
    std::vector<std::weak_ptr<IConnection>> mConnections;
    ThreadSafeQueue<ipc::Package> mPackagesToSend;

    void Broadcast(ipc::Package&);
    void SendBySubscription(ipc::Package&);

    void AddSubscription();
    void AddConnectionWeak(std::weak_ptr<IConnection>);

    bool CheckForOverload() const;
    void CleanExpiredConnections();
};