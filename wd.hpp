#pragma once
#include <string>

namespace dsh {
    extern std::string wd; // Current working directory for files.

    // Check if the current working directory is set.
    bool iscwdset();
}
