#include "err.hpp"
#include "log.hpp"
#include "fio.hpp"
#include "dpy.hpp"

// Open a display directory specified by the given path.
Dpy::Dpy(const char* path) {
    fd = ::open(path, O_DIRECTORY); 
    if (fd == -1)
        throw err("Failed to open display file!");
}

// Disconnect from the display.
Dpy::~Dpy() {
    // Close the file descriptor handle to the rectangular file.
    if (close(fd) == -1)
        error("Failed to close file.");
}
