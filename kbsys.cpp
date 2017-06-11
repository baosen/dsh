#include "kbsys.hpp"

// Keyboard system for file system.
namespace kbsys {
    Kb kb;
}

// Setup and initialize keyboard.
void kbsys::init() {
    // Open keyboard file.
    kb.open();
}

void kbsys::deinit() {
    kb.close();
}
