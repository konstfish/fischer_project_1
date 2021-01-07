/*
author: David Fischer
matnr:  i16079
file:   Coordinator.cpp
desc:   NVS Projekt 1 - Simulation of a distributed synchronisation using a central coordinator
class:  5C
catnr:  03
*/

#include "Coordinator.h"

using namespace std;

// IN : /
// OUT: /
// Debug function to print a diverse set of information, gathered from the node queue 
void Coordinator::print_queue(){
    cout << "Coord: Current Queue Size: " << node_queue.size() << endl;
    if(node_queue.size() >= 2){
        cout << "Coord: Current Node: " << node_queue.front() << endl;
        cout << "Coord: Last Node: " << node_queue.back() << endl;
    }
}

// IN : int id - Node ID
// OUT: /
// Adds the id to the queue and calls the condition variable to wait for a 
// node exiting the critical section
void Coordinator::message_req(int id){
    unique_lock<mutex> ul{mtx};

    node_queue.push(id);

    // print_queue();

    while(id != node_queue.front()){
        spot_taken.wait_for(ul, 1s);
    }

    collect_stats();

    //fmt::print(fg(fmt::color::light_salmon) | fmt::emphasis::italic,
    //    "Coord : OK to Node {}\n", id);
    spdlog::info("Coord : OK to Node {}", id);
}

// IN : int id - Node ID
// OUT: /
// Removes an id from the node queue and notifies the condition variable.
// Outputs an error if the id of the current node does not match the node trying to release the CS.
void Coordinator::message_rel(int id){
    unique_lock<mutex> ul{mtx};

    int removed = node_queue.front();
    
    if(removed != id){
        spdlog::critical("Coord : REL Request from Node {} didn't match current Node {}", id, removed);
        //fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
        //    "Coord : REL Request from Node {} didn't match current Node {}\n", id, removed);
    }else{
        node_queue.pop();
    }

    spot_taken.notify_one();
}


// IN :  bool http_server - starts the http server if requested
//       bool outage_dect - starts outage detection if requested
// OUT: /
void Coordinator::operator()(bool http_server, bool outage_dect){

    // Lambda thread to detect failed nodes
    thread t([&](){
        if(outage_dect){
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
                        // if the counter is able to count up to the timeout, the node is removed from the queue
                        st.failed_nodes += 1;
                        //fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                        //    "Coord : Node {} didn't respond within {} seconds, removing from Queue\n", cur_id, timeout);
                        spdlog::error("Coord : Node {} didn't respond within {} seconds, removing from Queue", cur_id, timeout);
                        node_queue.pop();
                        st.recoveries += 1;
                    }
                }
            }
        }
    });


    if(http_server){
        httplib::Server svr;

        // update thread pool (support 15 concurrent connections)
        svr.new_task_queue = [] { return new httplib::ThreadPool(15); };

        // customize server parameters
        svr.set_keep_alive_max_count(20);
        svr.set_keep_alive_timeout(90);

        // REQ route, calls the Coordinator::message_req function
        svr.Get("/req", [this](const httplib::Request& req, httplib::Response& res) {
            auto id = req.get_param_value("node_id");
            if(id == ""){
                res.set_content("Invalid Request", "text/plain");   
            }
            
            int conv = stoi(id);

            spdlog::info("HTTP: /req from {}", conv);

            message_req(conv);

            res.set_content("OK", "text/plain");
        });

        // REQ route, calls the Coordinator::message_rel function
        svr.Get("/rel", [this](const httplib::Request& req, httplib::Response& res) {
            auto id = req.get_param_value("node_id");
            if(id == ""){
                res.set_content("Invalid Request", "text/plain");   
            }
            
            int conv = stoi(id);

            spdlog::info("HTTP: /rel from {}", conv);


            message_rel(conv);

            res.set_content("Leaving Section!", "text/plain");
        });

        // get route, outputs the current stat table
        svr.Get("/get", [this](const httplib::Request& req, httplib::Response& res) {
            auto id = req.get_param_value("node_id");
            auto resp = dump_stat_table();
            res.set_content(resp, "text/plain");
        });

        svr.listen("127.0.0.1", 5001);
    }

    t.join();
}

// helper function to collect stats
void Coordinator::collect_stats(){
    st.admitted_nodes += 1;
    if(node_queue.size() > st.max_queue_size){
        st.max_queue_size = node_queue.size();
    }
}

// helper function to print the stat table
void Coordinator::output_stat_table(){
    auto duration = chrono::duration_cast<chrono::seconds> (std::chrono::system_clock::now() - start);
    int tmp = duration.count();

    if(tmp > 3){
        cout << Final Stats: << endl;
        std::cout << generate_stat_table() << endl;
    }
}

// helper function to dump the stat table into a string and return said string
string Coordinator::dump_stat_table(){
    ostringstream buf;
    buf << generate_stat_table() << endl;
    return buf.str();
}

// function to turn the StatContainer struct into a tabulate table and return it
tabulate::Table Coordinator::generate_stat_table(){
    auto duration = chrono::duration_cast<chrono::seconds> (std::chrono::system_clock::now() - start);

    int tmp = duration.count();

    tabulate::Table stat_table;

    size_t headers = 4;

    stat_table.add_row({"No. of Admitted Nodes", 
                        "Maximum Queue Size", 
                        "Failed Nodes/Recoveries",
                        "Total Time Spent Running"});

    stat_table.add_row({to_string(st.admitted_nodes), 
                        to_string(st.max_queue_size), 
                        to_string(st.failed_nodes) + '/' + to_string(st.recoveries),
                        to_string(tmp) + 's'});

    for (size_t i = 0; i < headers; ++i) {
        stat_table[0][i].format()
        .font_color(tabulate::Color::yellow)
        .font_align(tabulate::FontAlign::center)
        .font_style({tabulate::FontStyle::bold});
    }

    return stat_table;
}