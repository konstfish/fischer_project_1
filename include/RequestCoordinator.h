#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>

#include <fmt/core.h>
#include <fmt/color.h>

#include <httplib.h>

class RequestCoordinator{
    private:
    std::queue<int> node_queue;
    
    std::mutex mtx;
    std::condition_variable spot_taken;

    public:
    RequestCoordinator(){};

    void message_req(int id);
    void message_rel();

    void print_queue();

    void operator()();
};