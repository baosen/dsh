#include <sys/ioctl.h>
#include "log.hpp"
#include "fio.hpp"
#include "pos.hpp"
#include "wndctl.hpp"
#include "keywait.hpp"

// Test writing to x coordinate file.
static void xtest()
{
    auto fd = open("./sh/wnd/0/x", O_RDWR);

    if (fd < 0)
        die("Failed to open window 0!");

    const uint x = 200;
    if (write(fd, &x, sizeof(x)) < 0)
        syserror("Failed to write to x coordinate!");

    if (close(fd) < 0)
        die("Failed to close window 0!");
}

// Test writing to y coordinate file.
static void ytest()
{
    auto fd = open("./sh/wnd/0/y", O_RDWR);

    if (fd < 0)
        die("Failed to open window 0!");

    const uint y = 200;
    if (write(fd, &y, sizeof(y)) < 0)
        syserror("Failed to write to y coordinate!");

    if (close(fd) < 0)
        die("Failed to close window 0!");
}

// Test writing to ctl file.
static void ctltest()
{
    auto fd = open("./sh/wnd/0/ctl", O_RDWR);

    if (fd < 0)
        die("Failed to open window directory 0!");

    const auto p = pos(100, 100);
    if (ioctl(fd, wndctl::MOVE, &p) < 0)
        syserror("Failed to move window using ioctl(...)!");

    if (close(fd) < 0)
        die("Failed to close window directory 0!");
}

// Run window file tests.
int main()
{
    ctltest();
    keywait();

    xtest();
    keywait();

    ytest();
    keywait();

    return EXIT_SUCCESS;
}
