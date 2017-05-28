#include <cassert>
#include <sys/ioctl.h>
#include "fio.hpp"
#include "dpy.hpp"
#include "dpycmds.hpp"

#define WORKDIR "./hai/"

// Create display.
static bool create_display() {
    // Create file with user read and user write permissions.
    const auto fd = creat(WORKDIR "dpytest", S_IRUSR | S_IWUSR);
    if (fd == -1) {
        puts("Failed to create " WORKDIR "dpytest!");
        return false;
    }
    if (close(fd) == -1) {
        puts("Failed to close " WORKDIR "dpytest!");
        return false;
    }
    return true;
}

// Test controlling the display using ioctl().
static bool control_display() {
    const auto fd = open(WORKDIR "dpytest", O_RDWR);
    if (fd == -1) {
        puts("Failed to open " WORKDIR "dpytest!");
        return false;
    }
    // Test reset command.
    if (ioctl(fd, Dpycmd::reset) < 0) {
        puts("Failed to control device!");
        printf("errno: %d\n", errno);
        return false;
    }
    if (close(fd) == -1) {
        puts("Failed to close " WORKDIR " dpytest!");
        return false;
    }
    return true;
}

// Test opening non-existing display file.
static bool open_display() {
    const auto fd = open(WORKDIR "dpy0", O_RDWR);
    if (fd == -1) {
        puts("Failed to open " WORKDIR "dpy0!");
        printf("errno: %d\n", errno);
        return false;
    }
    return true;
}

// Test opening non-existing window file.
static bool open_window() {
    const auto fd = open(WORKDIR "wnd0", O_RDWR);
    if (fd == -1) {
        puts("Failed to open " WORKDIR "wnd0!");
        return false;
    }
    return true;
}

// Run test cases.
int main() {
    assert(open_display());
    //assert(open_window());
    assert(create_display());
    assert(control_display());
}
