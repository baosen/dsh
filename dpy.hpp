#pragma once
#include <string>

// Display
class Dpy {
public:
    // Open a display directory specified by the given path.
    Dpy(const char* path);
    ~Dpy();
private:
    int fd;
};
