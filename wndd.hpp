#pragma once
#include "dir.hpp"

// Window directory.
class wndd : public dir {
public:
    wndd(const std::string& name, const entlist& l);

    // IOCTL calls.
    enum {
        MOVE,
    };

    // Open window directory.
    virtual int open(const char *path) override;

    // Control window.
    virtual int ioctl(int   cmd,            // The ioctl() command number passed.
                      void *data) override; // The data.
};
