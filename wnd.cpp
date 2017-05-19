#include "frect.hpp"
#include "fb.hpp"
#include "wnd.hpp"
using namespace std;

// Create a new window.
Wnd::Wnd(const Pos& p) {
    if (dsh::iscwdset())
        cur = shared_ptr<Frect>(new Frect(p));
}

// Create an empty window.
Wnd::Wnd() {}

// Maximize the window.
void Wnd::max() {
    save();
}

// Minimize the window.
void Wnd::min() {
    save();
    //cur = Rect();
}

// Save old rectangle.
void Wnd::save() {
    old = cur;
}

// Click on window at position p.
void Wnd::click(const Pos& p) {
    // Is outside window rectangle?
    //if (p.x < cur.p.x || p.y < cur.p.y)
        //return;
}
