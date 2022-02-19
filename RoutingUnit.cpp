//
// Created by chi3hi on 09.02.22.
//

#include <thread>
#include <chrono>
#include <algorithm>
#include <unordered_set>

#include "RoutingUnit.h"

#include "SocketConnection.h"
#include "SQLiteQueries.h"
#include "MessageType.pb.cc"

std::mutex mutex;

RoutingUnit::RoutingUnit(uint32_t maxPossibleClientsCount, size_t capacity)
: mMessageCapacity(capacity)
, mMaxPossibleClientsCount(maxPossibleClientsCount)
, mSqliteUserData(std::make_unique<SQLiteUserData>())
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

RoutingUnit::~RoutingUnit() noexcept
{
    google::protobuf::ShutdownProtobufLibrary();
}

void RoutingUnit::PollQueue()
{
    auto pollingHandler = [self = this]{
        ipc::Package package;

        while(true)
        {
            package.Clear();
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
    auto socketConnection = std::make_shared<SocketConnection>(clientFd);

    while(socketConnection->IsConnected())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        size_t length = mMessageCapacity;
        char* buffer = new char[mMessageCapacity];

        auto result = socketConnection->Read(buffer, length);
        if(result == err_t::READING_FAILED)
            continue;
        if(result == err_t::CONNECTION_CLOSED)
            break;

        package.Clear();
        package.ParseFromArray(buffer, static_cast<int>(length));

        //TODO
        std::string userName = package.header().sender().sender();
        if(package.header().messagetype() == ipc::REGISTRATION)
        {
            //TODO
            if(!mSqliteUserData->IsUserRegistered(userName))
                mSqliteUserData->StoreNewUser(userName, 1);

            AddClientToMap(package.header().sender().sender(),
                           std::weak_ptr<IConnection>(socketConnection));

            std::cout << package.header().sender().sender() << " - registered." << std::endl;
            continue;
        }
        if(package.header().messagetype() == ipc::MESSAGE)
        {
            std::cout << "Message: " << package.payload().value()
                      << " -> from: " << package.header().sender().sender() << std::endl;

            mPackagesToSend.Push(package);
        }
    }
}

void RoutingUnit::Broadcast(ipc::Package& package) const
{
    std::string sender = package.header().sender().sender();
    size_t actualSize = package.ByteSizeLong();
    char* buffer = new char[actualSize];

    package.SerializeToArray(buffer, static_cast<int>(actualSize));

    for(auto& connection: mConnections)
    {
        if(connection.second.expired() || connection.first == sender)
            continue;

        connection.second.lock()->Write(buffer, actualSize);
    }

    delete[] buffer;
}

void RoutingUnit::Multicast(ipc::Package& package) const
{
    std::unordered_set<std::string> receivers;
    int receiversCount = package.header().receiver_size();

    for(auto i = 0; i < receiversCount; ++i)
        receivers.emplace(package.header().receiver()[i].receiver());

    size_t actualSize = package.ByteSizeLong();
    char* buffer = new char[actualSize];

    package.SerializeToArray(buffer, static_cast<int>(actualSize));

    for(auto& receiver: receivers)
    {
        auto desiredReceiver = mConnections.find(receiver);

        if(desiredReceiver == mConnections.cend() || desiredReceiver->second.expired())
            continue;

        desiredReceiver->second.lock()->Write(buffer, actualSize);
    }

    delete[] buffer;
}

void RoutingUnit::Unicast(ipc::Package &package) const
{
    std::string receiver = package.header().receiver().cbegin()->receiver();

    auto desiredReceiver = mConnections.find(receiver);

    if(desiredReceiver == mConnections.cend())
        return;

    size_t actualSize = package.ByteSizeLong();
    char* buffer = new char[actualSize];

    package.SerializeToArray(buffer, static_cast<int>(actualSize));

    if(!desiredReceiver->second.expired())
        desiredReceiver->second.lock()->Write(buffer, actualSize);

    delete[] buffer;
}

void RoutingUnit::AddClientToMap(std::string userName, std::weak_ptr<IConnection> connectionWeak)
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