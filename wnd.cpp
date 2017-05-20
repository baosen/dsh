#include "fio.hpp"
#include "frect.hpp"
#include "fb.hpp"
#include "wnd.hpp"
#include "wd.hpp"
#include "log.hpp"
using namespace std;

// Create a new window.
Wnd::Wnd(const Pos& p) {
    throw err("TODO!");
}

// Create an empty window.
Wnd::Wnd(const string& name_) {
    if (dsh::iscwdset()) {
        fd = ::open((dsh::wd+"/wnd/"+name_).c_str(), O_CREAT);
        if (fd == -1)
            throw err("Invalid name.");
        this->name = name; 
    }
}

// Create null window.
Wnd::Wnd() : fd(-2) {
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

// Click on window at position p.
void Wnd::click(const Pos& p) {
    // Is outside window rectangle?
    //if (p.x < cur.p.x || p.y < cur.p.y)
        //return;
}
