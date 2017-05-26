#include <cassert>
#include "fio.hpp"
#include "dpy.hpp"

// Test opening non-existing display file.
static bool dpyopen() {
    const auto fd = open("./hai/dpy0", O_RDWR);
    if (fd == -1) {
        puts("Failed to open ./hai/dpy0!");
        return false;
    }
    return true;
}

// Test opening non-existing window file.
static bool wndopen() {
    const auto fd = open("./hai/wnd0", O_RDWR);
    if (fd == -1) {
        puts("Failed to open ./hai/wnd0!");
        return false;
    }
    return true;
}

// Run test cases.
int main() {
    assert(dpyopen());
    assert(wndopen());
}
