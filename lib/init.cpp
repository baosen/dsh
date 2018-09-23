#include "msys.hpp"
#include "wsys.hpp"
#include "kbsys.hpp"

// Initialize shell.
void init() 
{
    // Setup mouse.
    msys::init();
    // Setup keyboard.
    kbsys::init();
    // Setup window.
    wsys::init();
}
