#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "frect.hpp"
#include "log.hpp"
using namespace std;

namespace {
    string wd; // Current working directory for file rectangles.
}

// Set current working directory for file rectangles.
void dsh::setcwd(const string& dir) {
    wd = string(dir);
}

// Check if current working directory is set.
bool dsh::iscwdset() {
    return !wd.size();
}

// Creates an empty rectangle in a file specified in the file system.
Frect::Frect(const string& name_) {
    fd = ::open((wd+name_).c_str(), O_CREAT);
    if (fd == -1)
        throw err("Invalid name.");
    this->name = name; 
}
// Accepts a pointer to a C string.
Frect::Frect(const char *name) : Frect(string(name)) {}

// Creates an empty rectangle positioned at p in a file specified before-hand.
Frect::Frect(const Pos& p) : Frect(wd) {
}

// Creates an empty rectangle in a file specified before-hand.
Frect::Frect() : Frect(wd) {}

// Closes and removes the rectangle file.
Frect::~Frect() {
    // Close the file descriptor handle to the rectangular file.
    if (close(fd) == -1)
        error("Failed to close file.");
    // Delete rectangular file.
    if (unlink((wd + this->name).c_str()) == -1)
        error("Faield to unlink file.");
}

// Fill rectangle with colour.
void Frect::fill(const Col& c) const {
}

// Returns the index to its position in the rectangle.
uint Frect::i() const {
}

// Returns the rectangle area size.
size_t Frect::size() const {
}

// Resize rectangle image.
void Frect::resize(const uint w, const uint h) {
}
