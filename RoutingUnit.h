//
// Created by chi3hi on 09.02.22.
//

#pragma once

#include <memory>
#include <unordered_map>

#include "ThreadSafeQueue.h"
#include "MessageType.pb.h"

class IConnection;
class SQLiteUserData;

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
    std::unique_ptr<SQLiteUserData> mSqliteUserData;
    ThreadSafeQueue<ipc::Package> mPackagesToSend;
    std::unordered_map<std::string, std::weak_ptr<IConnection>> mConnections;

    void Broadcast(ipc::Package&) const;
    void Multicast(ipc::Package&) const;
    void Unicast(ipc::Package&) const;

    void AddClientToMap(std::string userName, std::weak_ptr<IConnection>);
    bool CheckForOverload() const;
    void CleanExpiredConnections();
};
