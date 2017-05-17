#include <string>
#include "frect.hpp"
using namespace std;

namespace {
    string wd; // Current working directory for file rectangles.
}

namespace dsh {
    // Set current working directory for file rectangles.
    void setcwd(const char* dir) {
        wd = string(dir);
    }
}

// Creates an empty rectangle in a file on the file system.
Frect::Frect() {
}

// Closes and removes the rectangle file.
Frect::~Frect() {
}
