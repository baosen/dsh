#pragma once
#include <string>
#include "types.hpp"

// Client display
class Dpy {
public:
    // Open a display directory specified by the given path.
    Dpy(const std::string& path);
    // Close display.
    ~Dpy();
private:
    std::string dirpath; // Path to directory.
};
