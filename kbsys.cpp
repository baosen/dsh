#include "kbsys.hpp"

namespace kbsys {
    Kb kb;
}

// Setup and initialize keyboard.
void kbsys::init() {
    kb.open();
}
