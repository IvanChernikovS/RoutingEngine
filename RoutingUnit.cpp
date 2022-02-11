//
// Created by chi3hi on 09.02.22.
//

#include <thread>
#include <chrono>
#include <algorithm>

#include "RoutingUnit.h"

#include "SocketConnection.h"
#include "MessageType.pb.cc"

std::mutex mutex;

RoutingUnit::RoutingUnit(uint32_t maxPossibleClientsCount)
{
    mConnections.reserve(maxPossibleClientsCount);
}

RoutingUnit::~RoutingUnit() noexcept
{
    google::protobuf::ShutdownProtobufLibrary();
}

void RoutingUnit::PollQueue()
{
    auto pollingHandler = [self = this](){
        while(true)
        {
            ipc::Package package;
            package.Clear();
            self->mPackagesToSend.WaitAndPop(package);

            if(self->mConnections.empty()) //TODO
                break;

            self->Broadcast(package); //TODO
        }
    };

    std::thread tPolling(pollingHandler);
    if(tPolling.joinable())
        tPolling.detach();
}

void RoutingUnit::PollChanel(int clientFd, size_t capacity)
{
    auto socketConnection = std::make_shared<SocketConnection>(clientFd);

    AddConnectionWeak(std::weak_ptr<IConnection>(socketConnection));

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    ipc::Package package;

    while(socketConnection->IsConnected())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        size_t length = capacity;
        char* buffer = new char[capacity];
        auto result = socketConnection->Read(buffer, length);
        if(result == err_t::READING_FAILED)
            continue;
        if(result == err_t::CONNECTION_CLOSED)
            break;

        package.Clear();
        package.ParseFromArray(buffer, static_cast<int>(length));

        std::cout << "Message: " << package.payload().value() << std::endl;

        mPackagesToSend.Push(package);
    }
}

void RoutingUnit::Broadcast(ipc::Package& package)
{
    size_t actualSize = package.ByteSizeLong();
    char* buffer = new char[actualSize];

    package.SerializeToArray(buffer, static_cast<int>(actualSize));

    for(auto& connection: mConnections)
    {
        if(connection.expired())
            continue;

        connection.lock()->Write(buffer, actualSize);
    }

    if(mConnections.empty())
        delete[] buffer;
}

void RoutingUnit::SendBySubscription(ipc::Package& package)
{

}

void RoutingUnit::AddSubscription()
{

}

void RoutingUnit::AddConnectionWeak(std::weak_ptr<IConnection> connectionWeak)
{
    std::lock_guard<std::mutex> lg(mutex);

    if(CheckForOverload())
        CleanExpiredConnections();

    mConnections.emplace_back(std::move(connectionWeak));
}

bool RoutingUnit::CheckForOverload() const
{
    int delta = 5;
    return mConnections.size() > mConnections.capacity() - delta;
}

void RoutingUnit::CleanExpiredConnections()
{
    std::lock_guard<std::mutex> lg(mutex);
    mConnections.erase(std::remove_if(mConnections.begin(), mConnections.end(),
                                        [](std::weak_ptr<IConnection>& connection){
                                            return connection.expired();
                                        }),
                       mConnections.end());
}