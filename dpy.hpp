#pragma once
#include <string>

// Display
class Dpy {
public:
    // Open a display directory specified by the given path.
    Dpy(const char* path);
    // TODO: Connect to a remote network display.
    ~Dpy();
private:
    int fd;
};
