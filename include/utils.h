#pragma once

#include <iostream>
#include <csignal>

#include <fmt/core.h>
#include <fmt/color.h>

void signal_handler( int signum);

struct Options{
    bool simulate_node_outage;
    bool http_communication;

    Options(bool sno, bool http):simulate_node_outage( sno ), http_communication( http ){};
};

struct StatContainer{
    int admitted_nodes{0};
    size_t max_queue_size{0};
    int failed_nodes{0};
    int recoveries{0};
};