#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "frect.hpp"
using namespace std;

namespace {
    string wd; // Current working directory for file rectangles.
}

// Set current working directory for file rectangles.
void dsh::setcwd(const char* dir) {
    wd = string(dir);
}

// Creates an empty rectangle in a file on the file system.
Frect::Frect(const char *name) {
    fd = ::open((wd+name).c_str(), O_CREAT);
    if (fd == -1)
        throw err("Invalid name.");
    this->name = name; 
}

// Closes and removes the rectangle file.
Frect::~Frect() {
    // Close the file descriptor handle to the rectangular file.
    if (close(fd) == -1)
        throw err("Failed to close file.");
    // Delete rectangular file.
    if (unlink((wd + this->name).c_str()) == -1)
        throw err("Faield to unlink file.");
}
