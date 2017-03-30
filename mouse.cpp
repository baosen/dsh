#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/input.h>
#include "err.hpp"
#include "mouse.hpp"
using namespace std;

// Is bit set?
constexpr bool bset(const char n, const ushort i) {
    return !!(n & (1u << i));
}

// Check if it is a mouse.
bool mouse(char b[EV_MAX]) {
    bool key = false, rel = false;
    for (ushort i = 0; i < EV_MAX; i++) {
        if (bset(b[0], i)) {
            switch (i) {
            case EV_KEY:
                key = true;
                break;
            case EV_REL:
                rel = true;
                break;
            default:
                break;
            }
        }
    }
    return key && rel;
}

// Find a mouse and open it.
Mouse::Mouse(In& i) : oldl(false), oldr(false), oldm(false) {
    // Check if input device given has mouse capabilities.
}

// Make mouse event.
void Mouse::mk(deque<Evt::Evt>& d) {
    // Create event object.
    In::Evt ev;
    zero(ev);
    ev.d = In::Dev::Mouse;
    // Add button events.
    int l, m, r, wh;
    l = (e[0] & 1); // 1 bit is left mouse button pressed?
    if (oldl != l) {
        ev.type.m = In::MType::Left;
        oldl = ev.val.min.left = l; 
        d.push_back(ev);
    }
    r = ((e[0] >> 1) & 1); // 2 bit is right mouse button pressed?
    if (oldr != r) {
        ev.type.m = In::MType::Right;
        oldr = ev.val.min.right = r;
        d.push_back(ev);
    }
    m = ((e[0] >> 2) & 1); // 3 bit is middle mouse button pressed?
    if (oldm != m)
        d.push_back(ev);
    // Add X movement.
    ev.type.m = In::MType::X;
    ev.val.min.x = e[1]; // x.
    d.push_back(ev);
    // Add Y movement. Y is flipped here!
    ev.type.m = In::MType::Y;
    ev.val.min.y = e[2]*-1; // y.
    d.push_back(ev);
}

// Read mouse input.
deque<Mouse::Evt> Mouse::rd() {
}
