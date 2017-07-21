#pragma once
#include "dir.hpp"

// Window directory.
class wndd : public dir {
public:
    enum {
        MOVE,
    };

    // Open window directory.
    virtual int open(const char *path) override;

    // Control window.
    int ioctl(int   cmd,  // The ioctl() command number passed.
              void *arg); // The arguments provided to the ioctl() call.

};
