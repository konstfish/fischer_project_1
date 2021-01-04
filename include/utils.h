/*
author: David Fischer
matnr:  i16079
file:   Coordinator.h
desc:   NVS Projekt 1 - Simulation of a distributed synchronisation using a central coordinator
class:  5C
catnr:  03
*/

#pragma once

//#include <fmt/core.h>
//#include <fmt/color.h>

#include <spdlog/spdlog.h>

#include <iostream>
#include <csignal>

// signal handler outlinend in utils.cpp
void signal_handler(int signum);


// Options which are passed to the Node Class. (More expandable than just passing the variables themselfes)
struct Options{
    bool simulate_node_outage;
    bool http_communication;

    Options(bool sno, bool http):simulate_node_outage( sno ), http_communication( http ){};
};

//Statistic Collection Struct, used to generate the table, which is displayed on exit.
struct StatContainer{
    int admitted_nodes{0};
    size_t max_queue_size{0};
    int failed_nodes{0};
    int recoveries{0};
};