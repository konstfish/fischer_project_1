#pragma once

#include <iostream>

struct Options{
    bool simulate_node_outage;

    Options(bool sno):simulate_node_outage( sno ){};
};
