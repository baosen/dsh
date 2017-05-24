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

    void dpytest() {
        Dpy d("./dsh/");
    }

    // Test shell file system.
    void dshfstest() {
        // Create a display.
        const auto dfd = open("./hai/dpy0", O_CREAT);
        // Create a window.
        const auto wfd = open("./hai/wnd0", O_CREAT);
    }
}

// Run test cases.
int main() {
    dshfstest();
    //dpytest();
    //assert(kbtest());
    //assert(mtest());
}
