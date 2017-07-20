#pragma once
#include "dir.hpp"

// Window directory.
class wndd : public dir {
public:
    enum {
        MOVE,
    };

    // Control window.
    int ioctl(int   cmd,  // The ioctl() command number passed.
              void *arg); // The arguments provided to the ioctl() call.
};
