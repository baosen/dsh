#include "framebuffer.hpp"
#include "wnd.hpp"

Wnd::Wnd(const uint x, const uint y, const uint w, const uint h) 
    : x(x), y(y), width(w), height(h) {}

// Maximize the window.
void Wnd::max() {
    // Save old position.
    oldw = width;
    oldh = height;
    width = maxw();
    height = maxh();

    draw();
}

// Minimize the window.
void Wnd::min() {
}
