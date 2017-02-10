#include "fb.hpp"
#include "wnd.hpp"

// Create new window.
Wnd::Wnd(const Rect& r) : cur(r) {}

// Create null window.
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
    Fill(cur, c);
}
