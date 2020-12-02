#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>

#include <fmt/core.h>
#include <fmt/color.h>

#include <tabulate/table.hpp>

#include "utils.h"

class Coordinator{
    private:

    std::__1::chrono::system_clock::time_point start;

    std::queue<int> node_queue;
    
    std::mutex mtx;
    std::condition_variable spot_taken;

    StatContainer st;

    public:
    Coordinator(){
        start = std::__1::chrono::system_clock::now();
    };

    ~Coordinator(){
        output_stat_table();
    }

    void message_req(int id);
    void message_rel();

    void collect_stats();
    void output_stat_table();

    void print_queue();

    void operator()();
};