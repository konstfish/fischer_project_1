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

    while(id != node_queue.front()){
        spot_taken.wait_for(ul, 1s);
    }

    fmt::print(fg(fmt::color::light_salmon) | fmt::emphasis::italic,
        "Coord : OK to Node {}\n", id);
}

void Coordinator::message_rel(){
    unique_lock<mutex> ul{mtx};

    node_queue.pop();

    spot_taken.notify_one();
}


// only used to dected Node outages
void Coordinator::operator()(){
    int cnt{0};
    int timeout{8};
    int cur_id{-1};
    while(true){
        if(node_queue.size() > 0){
            this_thread::sleep_for(1s);
            if(node_queue.front() == cur_id){
                cnt += 1;
            }else{
                cur_id = node_queue.front();
                cnt = 0;
            }

            if(cnt == timeout){
                fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                    "Coord : Node {} didn't respond within {} seconds, removing from Queue\n", cur_id, timeout);
                node_queue.pop();
            }
        }
    }
}