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
    rcur = rold;
}

// Save old rectangle.
void Wnd::save() {
    // Save current position.
    pold = pcur;
    // Save current rectangle.
    rold = rcur;
}
