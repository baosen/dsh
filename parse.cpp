#include <cstring>
#include "log.hpp"
#include "wd.hpp"

namespace {
    // Device numbers.
    int mousenum = -1, 
        evm      = -1;
}

// Parse the arguments provided by the user.
void parse(const int argc, const char *argv[]) {
    // If argument provided.
    for (int i = 1; i < argc; ++i) {
        const auto s = argv[i];
        // Set working directory for window files.
        if (!strcmp(s, "-dir")) {
            char *path = nullptr;
            if (sscanf(s+5, "%ms", &path) < 0) // m is part of POSIX 2008 (2013).
                die("Invalid parameter.");
            dsh::wd = path;
        }
        // Set which "hacky" mouse to use.
        if (!strcmp(s, "-m")) 
            if (sscanf(s, "%d", &mousenum) < 0)
                die("Invalid parameter.");
        if (!strcmp(s, "-e")) // Set event device. Automatically detects type.
            if (sscanf(s, "%d", &evm) < 0)
                die("Invalid parameter.");
    }
}

