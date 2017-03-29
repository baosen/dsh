#include "in.hpp"
#include <iostream>
using namespace std;

// Return number of device files.
static uint nfiles() {
    return 3;
}

/*
// Discover generic "hacked" mouse.
static int discgen() {
    int fd, n = nfiles();
    stringstream s;
    for (int i = 0; i < n; ++i) {
        s << "/dev/input/mouse" << i;
        if ((fd = ::open(s.str().c_str(), O_RDONLY) != -1))
            return fd;
        s.str("");
    }
    throw err("No generic device found!");
}
*/

/*
// Discover mouse event file.
static int discevt() {
    int fd, n = nfiles();
    stringstream s;
    for (int i = 0; i < n; ++i) {
        s << "/dev/input/event" << i;
        if ((fd = ::open(s.str().c_str(), O_RDONLY) != -1))
            return fd;
        s.str("");
    }
    throw err("No event device found!");
}
*/

namespace {
    const char evtp[] = "/dev/input/event0"; // File path to the event-driven mouse device file.
    const char mp[]   = "/dev/input/mouse0"; // File path to the "hacky" generic mouse input device file.
}

int main() {
    In i(evtp);
    for (;;) {
        auto d = i.rd();
        for (const auto& e : d) {
            switch (e.d) {
            case In::Dev::Mouse: {
                switch (e.type.m) {
                case In::MType::Left:
                    cout << (e.val.min.left ? "left pressed!" : "left released!") << endl;
                    break;
                case In::MType::Right:
                    cout << (e.val.min.right ? "right pressed!" : "right released!") << endl;
                    break;
                case In::MType::Mid:
                    cout << (e.val.min.mid ? "middle pressed!" : "middle released!") << endl;
                    break;
                case In::MType::Wheel:
                    switch (e.val.min.wheel) {
                    case In::Scr::UP:   // Scroll upwards.
                        cout << "Upward scroll!" << endl;
                        break;
                    case In::Scr::DOWN: // Scroll downwards.
                        cout << "Downward scroll!" << endl;
                        break;
                    }  
                    break;
                case In::MType::X:
                    cout << "x: " << e.val.min.x << endl;
                    break;
                case In::MType::Y:
                    cout << "y: " << e.val.min.y << endl;
                    break;
                default:
                    break;
                }
                break;
            }
            default:
                break;
            }
        }
    }
    return 0;
}
