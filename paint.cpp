#include "fb.hpp"
#include "wnd.hpp"

namespace {
    void paint() {}
}

Wnd::Wnd(const uint x, const uint y, const uint w, const uint h) 
    : x(x), y(y), width(w), height(h) {}

// Maximize.
void Wnd::max() {
    // Save old position.
    oldw = width;
    oldh = height;
    width = maxw();
    height = maxh();

    // Repaint.
    paint();
}

// Minimize.
void Wnd::min() {
    paint();
}
