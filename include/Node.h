#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <random>
#include <sstream>


#include "utils.h"
class Node{
    private:
    int id{-1};



    public:
    Node(int i):id( i ){};

    int getId() { return id; }

    void message_ok();
    void operator()();
};