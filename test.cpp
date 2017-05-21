#include <cassert>
#include "kb.hpp"

namespace {
    // Test keyboard functions.
    bool kbtest() {
        Kb kb;
        for (;;)
            kb.get();
    }
    
    // Test mouse functions.
    bool mtest() {
        return false;
    }
}

// Run test cases.
void test() {
    assert(kbtest());
    assert(mtest());
}
