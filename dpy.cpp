#include "err.hpp"
#include "log.hpp"
#include "fio.hpp"
#include "dpy.hpp"

// Open a display directory specified by the given path.
Dpy::Dpy(const char* path) {
    fd = ::mkdir(path, 0600); 
    switch (fd) {
    case ENOSPC:
        throw err("Not enough space available!");
    case EROFS:
        throw err("Path is read-only!");
    case -1:
    default:
        throw err("Failed to open display file!");
        // TODO: Also throw errno.
    }
}

// Disconnect from the display.
Dpy::~Dpy() {
    // Close the file descriptor handle to the rectangular file.
    if (close(fd) == -1)
        error("Failed to close file.");
}
