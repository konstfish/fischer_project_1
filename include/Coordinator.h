#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <queue> 

class Coordinator{
    private:
    std::queue<int> node_queue;
    
    std::mutex mtx;
    std::condition_variable spot_taken;

    public:
    Coordinator(){};

    void message_req(int id);
    void message_rel();

    void print_queue();
};