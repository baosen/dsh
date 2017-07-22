#include "log.hpp"
#include "fio.hpp"

int main()
{
    auto fd = open("./sh/wnd/0/x", O_RDWR);
    if (fd < 0)
        die("Failed to open window 0!");

    uint x = 100;
    if (write(fd, &x, sizeof(x)) < 0)
        die("Failed to write to x coordinate!");

    if (close(fd) < 0)
        die("Failed to close window 0!");

    return EXIT_SUCCESS;
}
