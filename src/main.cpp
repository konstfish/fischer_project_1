
#include <iostream>
#include <thread>
#include <vector>

#include "CLI11.hpp"

#include "Coordinator.h"
#include "Node.h"

using namespace std;

int main(int argc, char* argv[]) {
    CLI::App app("Simulation einer verteilten Synchronisation mit einem zentralen Koordinator");

    int no_of_nodes{3};

    bool sim_node_outage{false};

    app.add_option("number", no_of_nodes, "Number of Nodes to create") -> required() 
    ->  check(CLI::Range(2,100).description("Range is limited to sensible values").active(true).name("range"));

    app.add_flag("-o, --outage", sim_node_outage, "Randomly forces nodes to fail, causing a deadlock");

    // app.add_flag("-r, --requests", io_async, "Use requests to communicate");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        return app.exit(e);
    }

    Coordinator coord;
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

    return 0;
}
