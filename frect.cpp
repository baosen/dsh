#include <sstream>
#include "wd.hpp"
#include "frect.hpp"
#include "log.hpp"
using namespace std;

// Creates an empty rectangle in a file specified before-hand.
Frect::Frect() {
    if (dsh::iscwdset()) {
        static uint index = 0;
        stringstream ss;
        ss << dsh::wd << "rect" << index;
        fd = ::open(ss.str().c_str(), O_CREAT);
        if (fd == -1)
            throw err("Invalid name.");
        this->name = ss.str(); 
    }
    throw err("Working directory is not set.");
}

// Creates an empty rectangle positioned at p in a file specified before-hand.
Frect::Frect(const Pos& p) : Frect() {
    throw err("TODO");
}

// Closes and removes the rectangle file.
Frect::~Frect() {
    // Close the file descriptor handle to the rectangular file.
    if (close(fd) == -1)
        error("Failed to close file.");
    // TODO: Delete file?
}

// Fill rectangle with colour.
void Frect::fill(const Col& c) const {
}

// Returns the index to its position in the rectangle.
uint Frect::i() const {
    throw err("TODO!");
}

// Returns the rectangle area size.
size_t Frect::size() const {
    throw err("TODO!");
}

// Resize rectangle image.
void Frect::resize(const uint w, const uint h) {
    throw err("TODO!");
}
