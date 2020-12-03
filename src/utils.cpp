#include "utils.h"

using namespace std;

void signal_handler(int signum) {
    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                    "\nInterrupt signal ({}) recieved!\n", signum);

    // since this exit is graceful, we can return 0
    exit(0);
}