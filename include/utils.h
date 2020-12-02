#pragma once

#include <iostream>

#include "Coordinator.h"

//void signal_handler( int signum);

struct Options{
    bool simulate_node_outage;

    Options(bool sno):simulate_node_outage( sno ){};
};