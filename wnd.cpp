#include <sstream>
#include "fio.hpp"
#include "frect.hpp"
#include "fb.hpp"
#include "wnd.hpp"
#include "wd.hpp"
#include "log.hpp"
using namespace std;

// Create a new window.
Wnd::Wnd(const Pos& p) : Wnd() {
    cur = shared_ptr<Frect>(new Frect());
}

// Create an empty window.
Wnd::Wnd() : cur(nullptr) {
    if (dsh::iscwdset()) {
        // Create wnd0, wnd1, wnd2 ... wndN files.
        static uint index = 0;
        stringstream ss;
        ss << dsh::wd << "/wnd" << index;
        fd = ::open(ss.str().c_str(), O_CREAT); 
        if (fd == -1)
            throw err("Invalid name.");
        this->name = ss.str(); 
        ++index;
        return;
    }
    throw err("Working directory is not set!");
}

// Destroy the window.
Wnd::~Wnd() {
    // Delete window file.
    if (unlink((dsh::wd + this->name).c_str()) == -1)
        error("Failed to unlink file.");
}

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
