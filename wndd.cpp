#include "wndd.hpp"
#include "errno.hpp"

// Control window.
int wndd::ioctl(int   cmd, // The ioctl() command number passed.
                void *arg) // The arguments provided to the ioctl() call.
{
    switch (cmd) {
    case wndd::MOVE:
        break;
    default:
        break;
    }
    return SUCCESS;
}
