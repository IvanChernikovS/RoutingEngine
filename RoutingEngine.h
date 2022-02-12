//
// Created by chi3hi on 11.02.22.
//

#pragma once

#include <memory>
#include <vector>
#include <future>

class RoutingUnit;
class Server;
struct config_t;

class RoutingEngine
{
public:
    explicit RoutingEngine(std::unique_ptr<config_t>&);
    ~RoutingEngine() noexcept;

    void Run();
    void WaitAndStop();
private:
    std::unique_ptr<RoutingUnit> mRoutingUnit;
    std::unique_ptr<Server> mServer;
    std::vector<std::future<int>> threadsPull;
};
