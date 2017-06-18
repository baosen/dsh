#include <cstring>
#include "wnd.hpp"

// Create a new window.
Wnd::Wnd(const Pos& p) // The position to place the window.
    : pcur(p) {}

// Create an empty window.
Wnd::Wnd() {}

// Destroy the window.
Wnd::~Wnd() {}

// Drive the window and handle window events.
void Wnd::run() {
}

// Maximize the window.
void Wnd::max() {
    save();
    rcur.max();
}

// Minimize the window.
void Wnd::min() {
    // Set the old rectangle as the current rectangle.
    rcur = rold;
    // Set old position as the current position.
    pcur = pold;
}

// Save old rectangle.
void Wnd::save() {
    // Save current position.
    pold = pcur;
    // Save current rectangle.
    rold = rcur;
}

// Read from the picture buffer of the window.
void Wnd::read(char *buf, off_t i,  size_t size) noexcept
{
    rcur.read(buf, i, size);
}

// Write to the picture buffer to the window. Returns exactly the number of bytes written except on error.
void Wnd::write(const char *buf, off_t i, size_t size) noexcept
{
    rcur.write(buf, i, size);
}
