#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "Node.h"

class Coordinator{
    private:
    int id{-1};

    std::vector<Node> queue;
    std::condition_variable spot_open;

    public:
    Coordinator(int i):id( i ){};

    int getId() { return id; }

    void message_req();
    void message_rel();
};