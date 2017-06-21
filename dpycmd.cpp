#include "dpycmds.hpp"

// Do display command.
int dpycmd(const int cmd) {
    switch (cmd) {
    case Dpycmd::reset:
        return 0;
    case Dpycmd::hz:
        return 0;
    case Dpycmd::res:
        return 0;
    default:
        break;
    };
    return -EINVAL;
}
