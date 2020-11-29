#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <random>
#include <sstream>


#include "utils.h"
#include "Coordinator.h"

class Node{
    private:
    int id{-1};

    Coordinator &coord;


    public:
    Node(int i, Coordinator &c):id( i ), coord( c ){};

    int getId() { return id; }

    void message_ok();
    void operator()();
};