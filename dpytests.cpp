#include <cassert>
#include <sys/ioctl.h>
#include "fio.hpp"
#include "dpy.hpp"

// Create display.
static bool create_display() {
    // Create file with user read and user write permissions.
    const auto fd = creat("./hai/dpy0", S_IRUSR | S_IWUSR);
    if (fd == -1) {
        puts("Failed to create ./hai/dpy0!");
        return false;
    }
    if (close(fd) == -1) {
        puts("Failed to close ./hai/dpy0!");
        return false;
    }
    return true;
}

// Test controlling the display using ioctl().
static bool control_display() {
    const auto fd = open("./hai/dpy0", O_RDWR);
    if (fd == -1) {
        puts("Failed to open ./hai/dpy0!");
        return false;
    }
    if (ioctl(fd, 12) < 0) {
        puts("Failed to control device!");
        printf("errno: %d\n", errno);
        return false;
    }
    if (close(fd) == -1) {
        puts("Failed to close ./hai/dpy0!");
        return false;
    }
    return true;
}

// Test opening non-existing display file.
static bool open_display() {
    const auto fd = open("./hai/dpy0", O_RDWR);
    if (fd == -1) {
        puts("Failed to open ./hai/dpy0!");
        return false;
    }
    return true;
}

// Test opening non-existing window file.
static bool open_window() {
    const auto fd = open("./hai/wnd0", O_RDWR);
    if (fd == -1) {
        puts("Failed to open ./hai/wnd0!");
        return false;
    }
    return true;
}

// Run test cases.
int main() {
    //assert(open_display());
    //assert(open_window());
    assert(create_display());
    assert(control_display());
}
