#pragma once
#include <memory>
#include "dir.hpp"
#include "file.hpp"

// Window ctl file.
class wndctl : public file {
public:
    wndctl();
    wndctl(const std::shared_ptr<class dir>& parent);

    // IOCTL calls.
    enum {
        MOVE,
    };

    // Control window.
    int ioctl(int   cmd,            // The ioctl() command number passed.
              void *data) override; // The data.
private:
    std::shared_ptr<class dir> parent;
};
