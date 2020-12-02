#pragma once

#include <iostream>
#include <csignal>

#include <fmt/core.h>
#include <fmt/color.h>

void signal_handler( int signum);

struct Options{
    bool simulate_node_outage;

    Options(bool sno):simulate_node_outage( sno ){};
};

struct StatContainer{
    int admitted_nodes{0};
    size_t max_queue_size{0};
    int failed_nodes{0};
    int recoveries{0};
};