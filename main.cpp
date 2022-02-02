#include <iostream>
#include <memory>
#include <thread>

#include "MessageType.pb.h"
#include "MessageType.pb.cc"

#include "SocketConnection.h"
#include "ConfigParser.h"

static std::string pathToJson = "/home/chi3hi/CLionProjects/CommunicationHub/Config.json";


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

            if(!socketConnection->IsConnected())
                return -1;

            size_t length = capacity;
            char* buffer = new char[capacity];

            GOOGLE_PROTOBUF_VERIFY_VERSION;

            while(socketConnection->Read(buffer, length) == err_t::SUCCESS)
            {
                ipc::Package package;
                package.ParseFromArray(buffer, length);

                std::cout << "Message: " << package.payload().value() << std::endl;

                size_t actualSize = package.ByteSizeLong();
                package.SerializeToArray(buffer, actualSize);

                if(socketConnection->Write(buffer, actualSize) != err_t::SUCCESS)
                    break;
            }
            google::protobuf::ShutdownProtobufLibrary();

            return 0;
        };

        std::thread t(connectionHandler);
        if(t.joinable())
            t.detach();
    }

    socketConnection->Disconnect();

    return 0;
}
