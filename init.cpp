#include "msys.hpp"
#include "wsys.hpp"
#include "kbsys.hpp"

// Initialize shell.
void init() {
    // Setup mouse.
    initm();
    // Setup keyboard.
    initkb();
    // Setup window.
    initw();
    // Setup network.
    //initnet();
}
