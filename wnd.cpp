#include "fb.hpp"
#include "wnd.hpp"

Wnd::Wnd(const Pos&, const Res&) {
}

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
    width = 0, height = 0;
}
