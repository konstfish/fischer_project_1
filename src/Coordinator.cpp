#include "Coordinator.h"

using namespace std;

void Coordinator::print_queue(){
    cout << "Coord: Current Queue Size: " << node_queue.size() << endl;
    cout << "Coord: Current Node: " << node_queue.front() << endl;
    cout << "Coord: Last Node: " << node_queue.back() << endl;
}

void Coordinator::message_req(int id){
    unique_lock<mutex> ul{mtx};

    node_queue.push(id);

    // print_queue();

    int cnt{0};

    while(id != node_queue.front() && cnt < 6){
        spot_taken.wait_for(ul, 1s);
        cnt+= 1;
    }

    if(cnt == 6){
        fmt::print(fg(fmt::color::crimson) | fmt::emphasis::italic,
            "Coord : Waited for 6 Seconds - Node {} has outage, removing from Network\n", id);
    }else{
        fmt::print(fg(fmt::color::light_salmon) | fmt::emphasis::italic,
            "Coord : OK to Node {}\n", id);
    }    
}

void Coordinator::message_rel(){
    unique_lock<mutex> ul{mtx};

    node_queue.pop();

    spot_taken.notify_one();
}