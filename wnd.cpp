#include "wnd.hpp"
#include "fbslt.hpp"

Wnd::Wnd(const Pos& p, const Res& r) {
    getfb().fill(Rect(p, r), 0) ;
}

// Maximize the window.
void Wnd::max() {
    save();
}

// Save old position.
void Wnd::save() {
    oldw = width;
    oldh = height;
    width = maxw();
    height = maxh();
}

// Minimize the window.
void Wnd::min() {
    width = 0, height = 0;
}
