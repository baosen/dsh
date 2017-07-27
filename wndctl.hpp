#pragma once
#include <memory>
#include <sys/ioctl.h>
#include "dir.hpp"
#include "file.hpp"
#include "pos.hpp"

// Window ctl file.
class wndctl : public file {
public:
    // Construct window ctl file with name as parent.
    wndctl(const std::string& pname);

    // IOCTL calls.
    enum {
        MOVE = _IOW(0, 0, pos), // Move window.
        CP   = _IOW(1, 0, pos)  // Get color properties.
    };

    // Control window.
    int ioctl(const int cmd,            // The ioctl() command number passed.
              void     *data) override; // The data.
private:
    std::string                pname;
};
