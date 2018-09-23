#pragma once
#include <string>
#include "types.hpp"

// Client display
class dpy {
public:
    // Open a display directory specified by the given path.
    dpy(const std::string& path);

    // Close display.
    ~dpy();
private:
    std::string dirpath; // Path to directory.
};
