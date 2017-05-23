#include <cassert>
#include "kb.hpp"
#include "dpy.hpp"

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

    void dpytest() {
        Dpy d("./dsh/");
    }
}

// Run test cases.
int main() {
    dpytest();
    //assert(kbtest());
    //assert(mtest());
}
