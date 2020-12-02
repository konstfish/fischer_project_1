/*
David Fischer
5CHIF

NVS Projekt 1 - 
*/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include "CLI11.hpp"

#include "utils.h"

#include "Coordinator.h"
#include "Node.h"

using namespace std;


/*
Ich wollt wirklich alles mögliche machen um das zu vermeiden aber am ende ist das trotzdem die "Sauberste" Lösung.

Andere optionen wären eine flag als globale variable, die mit dem signal handler geändert wird, dafür ist aber eine
while schleife im main nötig die diese permanent checkt (was ebenfalls nicht wirklich sauber ist)

stackoverflow hat mir leider auch nicht geholfen, da alle nur auf diverse lösungen mit globalen variablen verweisen

:(
*/

Coordinator coord;

int main(int argc, char* argv[]) {
    CLI::App app("Simulation einer verteilten Synchronisation mit einem zentralen Koordinator");

    int no_of_nodes{3};

    bool sim_node_outage{false};
    bool outage_detection{false};
    bool communication_via_req{false};

    // at about 300 threads /dev/urandom gives out, since too many threads are accessing it -> 200 is the logical maximum
    app.add_option("number", no_of_nodes, "Number of Nodes to create") -> required() 
        -> check(CLI::Range(2,200).description("Range is limited to sensible values").active(true).name("range"));

    CLI::Option *sim_outage = app.add_flag("-o, --outage-simulation", sim_node_outage, "Randomly forces nodes to fail, causing a deadlock");

    app.add_flag("-d, --outage-detection", outage_detection, "Detect failing nodes & remove them from the queue")->needs(sim_outage);

    app.add_flag("-r, --requests", communication_via_req, "Use requests to communicate");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        return app.exit(e);
    }
    
    // since this is optional, a unique_ptr handles thread creation
    unique_ptr<thread> thread_coord;

    if(outage_detection or communication_via_req){
        thread_coord = unique_ptr<thread>(new thread(ref(coord), communication_via_req, outage_detection));
    }

    // signal handler to catch Ctrl+C and output Stat Table (Through the Coordinators Destructor)
    signal(SIGINT, signal_handler);

    // create option struct
    Options opt(sim_node_outage, communication_via_req);

    // create vector of threads to store the nodes operator()() threads
    vector<thread> node_container;
    node_container.resize(no_of_nodes);

    for (int cnt = 0; cnt < no_of_nodes; cnt++) {
        Node tmp_node(cnt, ref(coord), opt);
        node_container.at(cnt) = thread{tmp_node};
    }


    // join threads from node_container
    for( auto &t : node_container ) {
        t.join();
    }

    // (optional): join coordinator operator()() thread
    if(outage_detection){
        (*thread_coord).join();
    }

    return 0;
}
