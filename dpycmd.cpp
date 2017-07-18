#include "dpycmds.hpp"

// Do display command.
int dpycmd(const int cmd) 
{
    switch (cmd) {
    case dpycmd::reset:
        return 0;
    case dpycmd::hz:
        return 0;
    case dpycmd::res:
        return 0;
    default:
        break;
    };
    return -EINVAL;
}
