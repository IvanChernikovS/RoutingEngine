//
// Created by chi3hi on 09.02.22.
//

#include <thread>
#include <chrono>
#include <algorithm>
#include <unordered_set>

#include "RoutingUnit.h"

#include "SocketConnection.h"
#include "MessageType.pb.cc"

std::mutex mutex;

RoutingUnit::RoutingUnit(uint32_t maxPossibleClientsCount, size_t capacity)
: mMessageCapacity(capacity)
, mMaxPossibleClientsCount(maxPossibleClientsCount)
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
        while(true)
        {
            ipc::Package package;
            package.Clear();
            self->mPackagesToSend.WaitAndPop(package);

            if(self->mConnections.empty()) //TODO
                break;

            if(package.header().receiver_size() > 1)
                self->Multicast(package);
            else
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

        if(package.header().messagetype() == ipc::REGISTRATION)
        {
            RegisterClient(package.header().sender().sender(),
                           std::weak_ptr<IConnection>(socketConnection));
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

decltype(auto) RoutingUnit::FindDesireReceiver(const std::string& receiver)
{
    auto isEqual = [&receiver](const auto& user){ return user.first == receiver; };
    return std::find_if(mConnections.cbegin(), mConnections.cend(), isEqual);
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

void RoutingUnit::Broadcast(ipc::Package& package)
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

void RoutingUnit::Multicast(ipc::Package& package)
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
        auto desiredReceiver = FindDesireReceiver(receiver);

        if(desiredReceiver == mConnections.cend() || desiredReceiver->second.expired())
            continue;

        desiredReceiver->second.lock()->Write(buffer, actualSize);
    }

    delete[] buffer;
}

void RoutingUnit::Unicast(ipc::Package &package)
{
    std::string receiver = package.header().receiver().cbegin()->receiver();

    auto desiredReceiver = FindDesireReceiver(receiver);

    if(desiredReceiver == mConnections.cend())
        return;

    size_t actualSize = package.ByteSizeLong();
    char* buffer = new char[actualSize];

    package.SerializeToArray(buffer, static_cast<int>(actualSize));

    if(!desiredReceiver->second.expired())
        desiredReceiver->second.lock()->Write(buffer, actualSize);

    delete[] buffer;
}

void RoutingUnit::RegisterClient(std::string userName, std::weak_ptr<IConnection> connectionWeak)
{
    std::lock_guard<std::mutex> lg(mutex);

    if(CheckForOverload())
        CleanExpiredConnections();

    mConnections.emplace(std::move(userName),std::move(connectionWeak));
}