#include <cassert>
#include "fio.hpp"
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

    // Open a display in the file-system.
    bool dpytest() {
        try {
            Dpy d("./dsh/");
            return false;
        } catch (...) {
            return false;
        }
    }

}

// Run test cases.
int main() {
    assert(kbtest());
    assert(mtest());
    assert(dpytest());
}
