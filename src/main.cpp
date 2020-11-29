
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

    app.add_option("number", no_of_nodes, "Number of Nodes to create") -> required() 
    ->  check(CLI::Range(2,100).description("range is limited to sensible values").active(true).name("range"));

    // app.add_flag("-a, --socket", io_async, "Use sockets to communicate");

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) { 
        return app.exit(e);
    }

    Coordinator c(1);

    vector<thread> node_container;
    node_container.resize(no_of_nodes);

    for (int cnt = 0; cnt < no_of_nodes; cnt++)
    {
        Node tmp_node(cnt);
        node_container.at(cnt) = thread{tmp_node};
        cout << node_container.at(cnt).get_id();
    }

    for( auto &t : node_container )
    {
        t.join();
    }

    /*for (int i = 0; i < no_of_nodes; i++){
        Node tmp_node(i);
        
        node_container.emplace_back([&](){ref(tmp_node);});
        cout << "no: " << node_container.size() << " - created: " << i << endl; 
    }

    cout << "no;: " << node_container.size() << endl; 

    for (std::thread &th : node_container)
    {
        th.join();
        cout << th.get_id() << endl;
    }*/

    return 0;
}
