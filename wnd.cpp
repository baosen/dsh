#include "fb.hpp"
#include "wnd.hpp"

// Create new window.
Wnd::Wnd(const Rect& r) : cur(r) {}

// Create empty window.
Wnd::Wnd() {}

// Maximize the window.
void Wnd::max() {
    save();
}

// Minimize the window.
void Wnd::min() {
    save();
    cur = Rect();
}

// Save old rectangle.
void Wnd::save() {
    old = cur;
}

// Fill entire window with colour c.
void Wnd::fill(const Col& c) {
    cur.fill(c);
}

// Click on window at position p.
void Wnd::click(const Pos& p) {
    // Is outside window rectangle?
    if (p.x < cur.p.x || p.y < cur.p.y)
        return;
}
