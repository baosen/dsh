#include <cassert>
#include <sys/ioctl.h>
#include "fio.hpp"
#include "dpycmds.hpp"

#define WORKDIR "./sh/"

// Create display.
bool create_display() 
{
    // Create file with user read and user write permissions.
    const auto fd = creat(WORKDIR "dpytest", S_IRUSR | S_IWUSR);

    if (fd < 0) {
        puts("Failed to create " WORKDIR "dpytest!");
        return false;
    }

    if (close(fd) < 0) {
        puts("Failed to close " WORKDIR "dpytest!");
        return false;
    }

    return true;
}

// Test controlling the display using ioctl().
bool control_display() 
{
    const auto fd = open(WORKDIR "dpytest", O_RDWR);

    if (fd < 0) {
        puts("Failed to open " WORKDIR "dpytest!");
        return false;
    }

    // Test reset command.
    if (ioctl(fd, dpycmd::reset) < 0) {
        printf("Failed to control " WORKDIR "dpytest! Errno: %d\n", errno);
        return false;
    }
    if (close(fd) < 0) {
        puts("Failed to close " WORKDIR "dpytest!");
        return false;
    }
    return true;
}

// Test opening existing display file.
bool open_display() 
{
    const auto fd = open(WORKDIR "dpy0", O_RDWR);
    if (fd < 0) {
        printf("Failed to open " WORKDIR "dpy0! Errno: %d\n", errno);
        return false;
    }
    return true;
}

// Test opening non-existing display file.
bool open_nonexisting_display() 
{
    const auto fd = open(WORKDIR "dpy0", O_RDWR);
    if (fd < 0 && errno == ENOENT) // Failed to open because no entry exists.
        return true;
    return false;
}

// Test opening window file.
bool open_window() 
{
    const auto fd = open(WORKDIR "wnd0", O_RDWR);
    if (fd < 0) {
        puts("Failed to open " WORKDIR "wnd0!");
        return false;
    }
    return true;
}

// Run test cases.
int main() 
{
    assert(open_nonexisting_display());
    assert(open_display());
    assert(create_display());
    assert(control_display());
    assert(open_window());

    return EXIT_SUCCESS;
}
