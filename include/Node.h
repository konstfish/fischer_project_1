/*
David Fischer (03)
5CHIF

NVS Projekt 1 - Simulation of a distributed synchronisation using a central coordinator
*/

#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <random>
#include <sstream>
#include <math.h>

/*
FINAL:
#define FMT_HEADER_ONLY
#include <fmt/format.h>
*/

#include <fmt/core.h>
#include <fmt/color.h>

#include <httplib.h>

#include "utils.h"
#include "Coordinator.h"

class Node{
    private:
    // Node id
    int id{-1};

    // Reference to the coordinator
    Coordinator &coord;

    // Options recieved from main
    Options opt;

    public:
    Node(int i, Coordinator &c, Options o):id( i ), coord( c ), opt( o ){};

    int getId() { return id; }

    void operator()();
};