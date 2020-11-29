#include "Node.h"

using namespace std;

void Node::operator()(){
    random_device rd;
    std::mt19937 gen{rd()}; std::uniform_real_distribution<> dis{3, 5};
    double seconds;

    std::mt19937 gen_outage{rd()}; std::uniform_real_distribution<> dis_outage{0, 100};
    double chance;

    ostringstream buf;

    while(true){

        buf << "Node " << id << ": preparing to enter critical section" << endl;
        cout << buf.str();
        buf.str("");

        seconds = dis(gen);
        this_thread::sleep_for(chrono::milliseconds{(int)(seconds * 1000)});

        buf << "Node " << id << ": REQ to enter critical section" << endl;
        cout << buf.str();
        buf.str("");

        // request kritischen abschnitt
        coord.message_req(id);

        buf << "Node " << id << ": Entering critical section" << endl;
        cout << buf.str();
        buf.str("");

        this_thread::sleep_for(chrono::seconds(4s));

        buf << "Node " << id << ": REL critical section" << endl;
        cout << buf.str();
        buf.str("");


        if(opt.simulate_node_outage){
            chance = dis_outage(gen_outage);
            if(chance > 95){
                buf << "Node " << id << ": Failing, shutting down!" << endl;
                cout << buf.str();
                buf.str("");
                break;
            }
        }
        coord.message_rel();
    }
}