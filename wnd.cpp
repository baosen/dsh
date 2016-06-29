#include "fb.hpp"
#include "wnd.hpp"

Wnd::Wnd(const Pos& p, const Res& r) {
    Fb fb;
    fb.fill(Rect(p, r), 0) ;
}

// Maximize the window.
void Wnd::max() {
    save();
}

// Minimize the window.
void Wnd::min() {
    r = Res(0, 0);
}

// Save old position.
void Wnd::save() {
    r = Res(maxw(), maxh());
}
