#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>

#include <fmt/core.h>
#include <fmt/color.h>

#include <tabulate/table.hpp>

struct StatContainer{
    int admitted_nodes{0};
    size_t max_queue_size{0};
    int failed_nodes{0};
    int recoveries{0};
};
class Coordinator{
    private:
    std::queue<int> node_queue;
    
    std::mutex mtx;
    std::condition_variable spot_taken;

    StatContainer st;

    public:
    Coordinator(){};

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