/*
author: David Fischer
matnr:  i16079
file:   Coordinator.h
desc:   NVS Projekt 1 - Simulation of a distributed synchronisation using a central coordinator
class:  5C
catnr:  03
*/

#include "Node.h"

using namespace std;

// Node operator function. Enters a while true loop to continualy request access to the
// critical section. Once granted, it enters the section, then leaves and releases it.
void Node::operator()(){
    random_device rd;

    // sleep a random amount of time
    std::mt19937 gen{rd()}; std::uniform_real_distribution<> dis{3, 5};
    double seconds;

    // generate 5% chance to fail
    std::mt19937 gen_outage{rd()}; std::uniform_real_distribution<> dis_outage{0, 100};
    double chance;

    ostringstream buf;

    // create httplib client
    httplib::Client cli("http://127.0.0.1:5001");

    // Worst case bei 10 nodes -> (5+4)*10
    cli.set_read_timeout(90, 0);
    cli.set_write_timeout(90, 0);

    while(true){

        seconds = dis(gen);

        //fmt::print("Node {}: Preparing to enter critical section ({}s)\n", id, (round(seconds*100)/100) );
        spdlog::info("Node {}: Preparing to enter critical section ({}s)", id, (round(seconds*100)/100) );

        this_thread::sleep_for(chrono::milliseconds{(int)(seconds * 1000)});

        spdlog::info("Node {}: REQ to enter critical section", id);

        // request critical section

        if(opt.http_communication){
            string url = "/req?node_id="+to_string(id);
            auto res = cli.Get(url.c_str());
            // cout << res->status << endl;
        }else{
            coord.message_req(id);
        }

        // Colors work well to quickly identify incorrect output.
        // blue & green should always alternate, otherwise 2 Nodes
        // could be in the critical section at once

        //fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
        //     "Node {}: Entering critical section\n", id);

        spdlog::info("Node {}: Entering critical section", id);

        this_thread::sleep_for(chrono::seconds(4s));

        if(opt.simulate_node_outage){
            chance = dis_outage(gen_outage);
            if(chance > 95){
                spdlog::critical("Node {}: Failing, shutting down!", id);

                //fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                //    "Node {}: Failing, shutting down!\n", id);
                break;
            }
        }

        //fmt::print(fg(fmt::color::spring_green) | fmt::emphasis::italic,
        //    "Node {}: REL critical section\n", id);

        spdlog::info("Node {}: REL critical section", id);

        if(opt.http_communication){
            string url = "/rel?node_id="+to_string(id);
            auto res = cli.Get(url.c_str());
            // cout << res->status << endl;
        }else{
            coord.message_rel(id);
        }
    }
}