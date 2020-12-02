
#include <iostream>
#include <thread>
#include <vector>
#include <csignal>
#include <mutex>

#include "CLI11.hpp"

#include "utils.h"

#include "Coordinator.h"
#include "Node.h"

#include "RequestNode.h"

using namespace std;

Coordinator coord;

int main(int argc, char* argv[]) {
    CLI::App app("Simulation einer verteilten Synchronisation mit einem zentralen Koordinator");

    int no_of_nodes{3};

    bool sim_node_outage{false};
    bool outage_detection{false};

    app.add_option("number", no_of_nodes, "Number of Nodes to create") -> required() 
        -> check(CLI::Range(2,100).description("Range is limited to sensible values").active(true).name("range"));

    CLI::Option *sim_outage = app.add_flag("-o, --outage-simulation", sim_node_outage, "Randomly forces nodes to fail, causing a deadlock");

    app.add_flag("-d, --outage-detection", outage_detection, "Detect failing nodes & remove them from the queue")->needs(sim_outage);

    // app.add_flag("-r, --requests", io_async, "Use requests to communicate");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        return app.exit(e);
    }

    unique_ptr<thread> thread_coord;

    if(outage_detection){
        thread_coord = unique_ptr<thread>(new thread(ref(coord)));
    }

    signal(SIGINT, signal_handler);

    /*RequestNode tmp(1, ref(coord), opt);
    thread t1{tmp};

    t1.join();

    this_thread::sleep_for(10s);
    */

    Options opt(sim_node_outage);

    vector<thread> node_container;
    node_container.resize(no_of_nodes);

    for (int cnt = 0; cnt < no_of_nodes; cnt++) {
        Node tmp_node(cnt, ref(coord), opt);
        node_container.at(cnt) = thread{tmp_node};
    }

    for( auto &t : node_container ) {
        t.join();
    }

    if(outage_detection){
        (*thread_coord).join();
    }

    return 0;
}
