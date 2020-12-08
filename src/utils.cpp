/*
David Fischer (03)
5CHIF

NVS Projekt 1 - Simulation of a distributed synchronisation using a central coordinator
*/

#include "utils.h"

using namespace std;

// Catches SIGINT and displays a Message. The global Coordinator calls its Destructor, which prints the table.  
void signal_handler(int signum) {
    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                    "\nInterrupt signal ({}) recieved!\n", signum);

    // since this exit is "graceful", we can return 0
    exit(0);
}