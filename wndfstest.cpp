#include <sys/ioctl.h>
#include "log.hpp"
#include "fio.hpp"
#include "wndd.hpp"

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

static void dirtest()
{
    auto fd = open("./sh/wnd/0", O_RDWR);
    if (fd < 0)
        die("Failed to open window directory 0!");

    if (ioctl(fd, wndd::MOVE) < 0)
        die("ioctl");

    if (close(fd) < 0)
        die("Failed to close window directory 0!");
}

int main()
{
    dirtest();
    return EXIT_SUCCESS;
}
