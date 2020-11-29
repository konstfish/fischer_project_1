
#include <iostream>
#include <thread>

#include "CLI11.hpp"

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
}
