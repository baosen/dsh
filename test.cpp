#include <cassert>
#include "kb.hpp"

// Test keyboard functions.
static bool kbtest() {
    Kb kb;
    for (;;)
        kb.get();
}

// Run test cases.
void test() {
    assert(kbtest());
}
