#include <sys/ioctl.h>
#include "log.hpp"
#include "fio.hpp"
#include "pos.hpp"
#include "wndctl.hpp"

static void xtest()
{
    auto fd = open("./sh/wnd/0/x", O_RDWR);

    if (fd < 0)
        die("Failed to open window 0!");

    uint x = 100;
    if (write(fd, &x, sizeof(x)) < 0)
        die("Failed to write to x coordinate!");

    if (close(fd) < 0)
        die("Failed to close window 0!");
}

static void ctltest()
{
    auto fd = open("./sh6/wnd/0/ctl", O_RDWR);

    if (fd < 0)
        die("Failed to open window directory 0!");

    const auto p = pos(100, 100);
    if (ioctl(fd, wndctl::MOVE, &p) < 0)
        die("ioctl() error.");

    if (close(fd) < 0)
        die("Failed to close window directory 0!");
}

int main()
{
    ctltest();
    return EXIT_SUCCESS;
}
