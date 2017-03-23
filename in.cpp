#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include "log.hpp"
#include "mouse.hpp"
using namespace std;

namespace {
    const char GENERIC[] = "Generic mouse";     // Name of /dev/input/mouse* to return.
    const char evtp[]    = "/dev/input/event7"; // File path to the event-driven mouse device file.
    const char mp[]      = "/dev/input/mouse0"; // File path to the generic mouse input device file.
    // What about touch pads?
}

static uint nevtfiles() {
    return 3;
}

// Discover generic "hacked" mouse.
static int discgen() {
    int fd, n = nevtfiles();
    stringstream s;
    for (int i = 0; i < n; ++i) {
        s << "/dev/input/mouse" << i;
        if ((fd = ::open(s.str().c_str(), O_RDONLY) != -1))
            return fd;
        s.str("");
    }
    throw err("No generic mouse found!");
}

// Discover mouse event file.
static int discevt() {
    int fd, n = nevtfiles();
    stringstream s;
    for (int i = 0; i < n; ++i) {
        s << "/dev/input/event" << i;
        if ((fd = ::open(s.str().c_str(), O_RDONLY) != -1))
            return fd;
        s.str("");
    }
    throw err("No event mouse found!");
}

// Open mouse input device file.
Mouse::Mouse() {
    stringstream ss;
    // Event-driven mouse input using event files.
    if ((fd = ::open(evtp, O_RDONLY)) != -1) {
        path = evtp;
        evt = true;
        cout << "Event mouse" << endl;
        return;
    }
    ss << "Cannot open " << evtp << ": " << strerror(errno);
    error(ss.str());
    // Generic mouse input using mouse0 device file.
    if ((fd = ::open(mp, O_RDONLY)) != -1) {
        path = mp; 
        evt = false;
        cout << GENERIC << endl;
        return;
    }
    ss.str("");
    ss << "Cannot open " << mp << ": " << strerror(errno);
    die(ss.str().c_str());
}

// Get the name of the mouse device.
string Mouse::name() {
    char buf[256] = {0};
    if (evt) {
        int err;
        if ((err = ioctl(fd, EVIOCGNAME(sizeof(buf)), buf)) >= 0)
            return string(buf);
        else
            throw err;
    }
    return GENERIC;
}

// Close mouse input device file.
Mouse::~Mouse() {
    stringstream ss;
    if (::close(fd) == -1) {
        ss << "Cannot close " << path << ": " << strerror(errno);
        die(ss.str().c_str());
    }
}

// Mouse button press or release.
static tuple<Mouse::Type, int> key(const __u16 code, const __s32 val) {
    switch (code) {
    case BTN_LEFT:    // Left mouse button.
        return make_tuple(Mouse::Type::LEFT, val);
    case BTN_RIGHT:   // Right mouse button.
        return make_tuple(Mouse::Type::RIGHT, val);
    case BTN_MIDDLE:  // Middle mouse button.
        return make_tuple(Mouse::Type::MID, val);
    case BTN_SIDE:    // Side mouse button.
        return make_tuple(Mouse::Type::SIDE, val);
    case BTN_EXTRA:   // Extra mouse button?
        return make_tuple(Mouse::Type::EXTRA, val);
    case BTN_FORWARD: // Forward button.
        return make_tuple(Mouse::Type::FORWARD, val);
    case BTN_BACK:    // Back button (to go backwards in browser?).
        return make_tuple(Mouse::Type::BACK, val);
    case BTN_TASK:    // Task button.
        return make_tuple(Mouse::Type::TASK, val);
    }
}

// This is mouse movement.
static tuple<Mouse::Type, int> rel(const __u16 code, const __s32 val) {
    cout << "EV_REL: ";
    // Mouse movements follows top-left coordinate system, 
    // where origo is at the top left of the screen and the positive y-axis points downwards.
    switch (code) {
    case 0: // x-axis, - left, + right.
        return make_tuple(Mouse::Type::X, val);
    case 1: // y-axis, - upwards, + downwards.
        return make_tuple(Mouse::Type::Y, val);
    case 8: // scroll.
        return make_tuple(Mouse::Type::SCR, val);
    }
}

// Read mouse event device file.
static tuple<Mouse::Type, int> evtrd(const int fd) {
    input_event e;
    while (::read(fd, &e, sizeof e)) {
        switch (e.type) {
        case EV_REL: // Relative motion.
            return rel(e.code, e.value);
        case EV_KEY: // Mouse button press and release.
            return key(e.code, e.value);
        case EV_SYN: // Synthetic events.
            cout << "EV_SYN: " << e.value << endl;
            break;
        case EV_ABS: // Absolute motion.
            cout << "EV_ABS: " << e.value << endl;
            break;
        case EV_MSC: // Miscellanous?
            cout << "EV_MSC: " << e.value << endl;
            break;
        default:
            cout << "Unknown type:" << hex << setw(2) << e.type << endl;
            break;
        }
    }
}

// Read mouse input from mouse device file
tuple<Mouse::Type, int> Mouse::read() {
    // Is using event-drive mouse device file?
    if (evt)
        return evtrd(fd);
    // Read using generic mouse device file.
    char e[4], x, y;
    int left, mid, right, wheel;
    while (::read(fd, &e, sizeof e)) {
        left  = e[0] & 1;        // 1 bit is left mouse button pressed?
        right = (e[0] >> 1) & 1; // 2 bit is right mouse button pressed?
        mid   = (e[0] >> 2) & 1; // 3 bit is middle mouse button pressed?
        x     = e[1];
        y     = e[2];
        wheel = e[3]; // mouse wheel change (bao: does not work!).
        printf("x=%d, y=%d, left=%d, middle=%d, right=%d, wheel=%d\n", x, y, left, mid, right, wheel);
    }
    return make_tuple(Mouse::Type::Y, 0); // TODO: Placeholder.
}
