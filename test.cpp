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

    void dshfstest() {
        puts("testing");
        const auto fd = open("./hai/hei", O_CREAT);
    }
}

// Run test cases.
int main() {
    dshfstest();
    //dpytest();
    //assert(kbtest());
    //assert(mtest());
}
