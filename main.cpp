#include <iostream>
#include <memory>
#include <thread>
#include <atomic>

#include "MessageType.pb.h"

#include "SocketConnection.h"
#include "Message.h"
#include "ConfigParser.h"

std::atomic_uint32_t threadIndex(0);
std::string pathToJson = "/home/chi3hi/CLionProjects/CommunicationHub/Config.json";


int main(int argc, char* argv[])
{
    ConfigParser configParser;
    if(!configParser.Parse(pathToJson.c_str()))
    {
        std::cout << "Invalid parsing" << std::endl;
        return -1;
    }

    std::shared_ptr<IConnection> socketConnection =
            std::make_shared<SocketConnection>(configParser.GetConfig()->ipAddress, configParser.GetConfig()->port);

    if(socketConnection->Connect() != err_t::SUCCESS)
        return -1;

    while(socketConnection->TryAccept() == err_t::SUCCESS)
    {
        auto connectionHandler = [socketConnection = socketConnection,
                                  capacity = configParser.GetConfig()->messageCapacity](){

            Message message(capacity);

            if(!socketConnection->IsConnected())
                return -1;

            ++threadIndex;

            while(socketConnection->Read(message) == err_t::SUCCESS)
            {
                if(socketConnection->Write(message) != err_t::SUCCESS)
                    return -1;
            }
            return 0;
        };

        std::thread t(connectionHandler);
        if(t.joinable())
            t.detach();
    }

    socketConnection->Disconnect();

    return 0;
}
