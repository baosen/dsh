#include "fb.hpp"
#include "wnd.hpp"

Wnd::Wnd(const Rect& r, const Col& bg) : cur(r), bg(bg) {
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
    //old = cur;
}

void Wnd::draw() {
    Fb fb;
    fb.fill(cur, bg);
}
