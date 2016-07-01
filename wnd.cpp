#include "fb.hpp"
#include "wnd.hpp"

Wnd::Wnd(const Rect& r) {
    Fb fb;
    fb.fill(Rect(p, r), 0) ;
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
    fb.fill(Rect(p, r), Col(255, 0, 0));
}
