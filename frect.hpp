#pragma once
#include "rect.hpp"

// File rectangle.
// The rectangle is stored as a file in the file system.
class Frect : public Rect {
public:
    Frect(const char *name);
    ~Frect();
private:
    int fd;           // File descriptor.
    std::string name; // Name of the file for storing the rectangular image.
};

namespace dsh {
    void setcwd(const string& dir);
}
