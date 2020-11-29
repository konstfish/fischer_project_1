#pragma once

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Node{
    private:
    int id{-1};



    public:
    Node(int i):id( i ){};

    int getId() { return id; }

    void message_ok();
    void operator()();
};