#include <sstream>
#include "fb.hpp"
#include "wnd.hpp"
#include "wd.hpp"
#include "log.hpp"
using namespace std;

// Create a new window.
Wnd::Wnd(const Pos& p) // The position to place the window.
    : cur(p) {}

// Create an empty window.
Wnd::Wnd() {}

// Destroy the window.
Wnd::~Wnd() {}

// Drive the window and handle window events.
void Wnd::run() {
}

// Maximize the window.
void Wnd::max() {
    save();
    rect.max();
}

// Minimize the window.
void Wnd::min() {
    save();
    // TODO!
}

// Save old rectangle.
void Wnd::save() {
    old = cur;
}
