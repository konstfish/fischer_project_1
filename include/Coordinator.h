/*
David Fischer (03)
5CHIF

NVS Projekt 1 - Simulation of a distributed synchronisation using a central coordinator
*/

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

        // set start time_point 
        std::chrono::system_clock::time_point start;

        // node queue to handle requests and releases on critical section
        std::queue<int> node_queue;
        
        // condition variable
        std::mutex mtx;
        std::condition_variable spot_taken;

        // StatContainer struct to easily manage statistics
        StatContainer st;
    public:
        // Constructor to set start point
        Coordinator(){
            start = std::chrono::system_clock::now();
        };

        // destructor to output tablulate table
        ~Coordinator(){
            output_stat_table();
        }

        // handle requests and releases from nodes
        void message_req(int id);
        void message_rel(int id);

        // functions to collect/handle and output statistics
        void collect_stats();
        void output_stat_table();
        tabulate::Table generate_stat_table();
        std::string dump_stat_table();

        // debug function to print information from queue
        void print_queue();

        // operator function
        void operator()(bool http_server, bool outage_dect);
};