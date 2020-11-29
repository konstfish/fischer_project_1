#include "Coordinator.h"

using namespace std;

void Coordinator::print_queue(){
    unique_lock<mutex> ul{mtx};

}

void Coordinator::message_req(int id){
    unique_lock<mutex> ul{mtx};

    node_queue.push(id);

    print_queue();
    cout << node_queue.front() << endl;

    while(id != node_queue.front()){
        spot_taken.wait(ul);
    }

    //spot_taken.wait(ul, [&](){return (id != node_queue.front());});
    
}

void Coordinator::message_rel(){
    unique_lock<mutex> ul{mtx};

    node_queue.pop();

    spot_taken.notify_one();
}