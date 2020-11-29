#include "Node.h"

using namespace std;

void Node::operator()(){
    while(true){
        cout << id << endl;
        this_thread::sleep_for(chrono::seconds(1s));
    }
}