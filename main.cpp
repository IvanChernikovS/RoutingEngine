#include <iostream>
#include <memory>

#include "Config.h"
#include "ConfigParser.h"
#include "RoutingEngine.h"

int main(const int argc, const char** argv)
{
    auto config = std::make_unique<config_t>();
    auto configParser = std::make_unique<ConfigParser>();
    if(argc <= 1 && !argv[1])
    {
        std::cout << "Should be path to jason as program arguments" << std::endl;
        return -1;
    }
    if(!configParser->Parse(argv[1], config))
    {
        std::cout << "Invalid parsing" << std::endl;
        return -1;
    }

    auto routingEngine = std::make_shared<RoutingEngine>(config);

    routingEngine->Run();
    routingEngine->WaitAndStop();

    return 0;
}
