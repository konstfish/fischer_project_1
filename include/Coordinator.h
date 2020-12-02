#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>
#include <sstream>

#include <fmt/core.h>
#include <fmt/color.h>

#include <tabulate/table.hpp>

#include <httplib.h>

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
        void message_rel(int id);

        void collect_stats();
        void output_stat_table();
        tabulate::Table generate_stat_table();
        std::string dump_stat_table();

        void print_queue();

        void http_server();

        void operator()(bool http_server, bool outage_dect);
};