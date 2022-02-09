#include <iostream>
#include <memory>
#include <thread>
#include <future>
#include <mutex>
#include <vector>

#include "MessageType.pb.h"
#include "MessageType.pb.cc"

#include "Server.h"
#include "SocketConnection.h"
#include "ConfigParser.h"
#include "ThreadSafeQueue.h"

std::vector<std::weak_ptr<IConnection>> connections;
ThreadSafeQueue<ipc::Package> packagesToSend;

std::mutex mtx;

void pollQueue()
{
    char* buffer = nullptr;

    while(true)
    {
        if(packagesToSend.Empty())
            continue;

        ipc::Package package;
        packagesToSend.WaitAndPop(package);
        size_t actualSize = package.ByteSizeLong();
        buffer = new char[actualSize];
        package.SerializeToArray(buffer, static_cast<int>(actualSize));

        if(connections.empty())
            break;

        for(auto& connection: connections)
        {
            if(connection.expired())
                continue;

            connection.lock()->Write(buffer, actualSize);
        }
    }

    delete[] buffer;
}

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

    uint32_t maxPossibleClientCount = configParser.GetConfig()->serverCapacity;
    connections.reserve(maxPossibleClientCount);

    auto server = std::make_unique<Server>(configParser.GetConfig()->ipAddress,
                                           configParser.GetConfig()->port,
                                           maxPossibleClientCount);

    if(!server->Connect())
        return -1;

    std::thread tPolling(pollQueue);
    if(tPolling.joinable())
        tPolling.detach();

    auto connectionHandler = [capacity = configParser.GetConfig()->messageCapacity](int clientFd){

        if(clientFd <= 0)
            return -1;

        auto socketConnection = std::make_shared<SocketConnection>(clientFd);
        {
            std::lock_guard<std::mutex> lg(mtx);
            connections.emplace_back(std::weak_ptr<IConnection>(socketConnection));
        }

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

            packagesToSend.Push(package);
        }
        return 0;
    };

    std::vector<std::future<int>> threadsPull;
    threadsPull.reserve(maxPossibleClientCount);

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

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
