#include "fb.hpp"
#include "wnd.hpp"

Wnd::Wnd(const Rect& r) : cur(r) {
    draw();
}

// Maximize the window.
void Wnd::max() {
    save();
}

// Minimize the window.
void Wnd::min() {
}

// Save old position.
void Wnd::save() {
    old = cur;
}

void Wnd::draw() {
    Fb fb;
    fb.fill(cur, Col(255, 0, 0));
}
