#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <random>
#include <sstream>
#include <math.h>

#include <fmt/core.h>
#include <fmt/color.h>

#include "utils.h"
#include "Coordinator.h"
class Node{
    private:
    int id{-1};

    Coordinator &coord;
    Options opt;

    public:
    Node(int i, Coordinator &c, Options o):id( i ), coord( c ), opt( o ){};

    int getId() { return id; }

    void operator()();
};