#include <iostream>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include "zero.hpp"
#include "log.hpp"
#include "in.hpp"
using namespace std;

namespace {
    const char GENERIC[] = "Generic mouse";     // Name of /dev/input/mouse* to return.
    const char evtp[]    = "/dev/input/event0"; // File path to the event-driven mouse device file.
    const char mp[]      = "/dev/input/mouse0"; // File path to the "hacky" generic mouse input device file.
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

// Open input device file.
In::In() {
    stringstream ss;
    // Event-driven input using event* device file.
    goto skip;
    if ((fd = ::open(evtp, O_RDONLY)) != -1) {
        path = evtp;
        evt = true;
        //cout << "Event mouse" << endl;
        return;
    }
    ss << "Cannot open " << evtp << ": " << strerror(errno);
    error(ss.str());
skip:
    // Generic input using mouse* device file.
    if ((fd = ::open(mp, O_RDONLY)) != -1) {
        path = mp; 
        evt = false;
        //cout << GENERIC << endl;
        return;
    }
    ss.str("");
    ss << "Cannot open " << mp << ": " << strerror(errno);
    die(ss.str().c_str());
}

// Get the name of the mouse device.
string In::name() {
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
In::~In() {
    stringstream ss;
    if (::close(fd) == -1) {
        ss << "Cannot close " << path << ": " << strerror(errno);
        die(ss.str().c_str());
    }
}

// Mouse button press or release.
static void key(In::Evt& ev, input_event& e) {
    switch (e.code) {
    case BTN_LEFT:    // Left mouse button.
        ev.type.m = In::MType::Left;
        ev.val.min.left = e.value;
        break;
    case BTN_RIGHT:   // Right mouse button.
        ev.type.m = In::MType::Right;
        ev.val.min.right = e.value;
        break;
    case BTN_MIDDLE:  // Middle mouse button.
        ev.type.m = In::MType::Mid;
        ev.val.min.mid = e.value;
        break;
    case BTN_SIDE:    // Side mouse button.
        ev.type.m = In::MType::Side;
        ev.val.min.side = e.value;
        break;
    case BTN_EXTRA:   // Extra mouse button?
        ev.type.m = In::MType::Extra;
        break;
    case BTN_FORWARD: // Forward button.
        ev.type.m = In::MType::Forward;
        break;
    case BTN_BACK:    // Back button (to go backwards in browser?).
        ev.type.m = In::MType::Back;
        break;
    case BTN_TASK:    // Task button.
        ev.type.m = In::MType::Task;
        break;
    default:
        break;
    }
}

// Mouse movement.
static void rel(In::Evt& ev, input_event& e) {
    // Mouse movements follows top-left coordinate system, where origo is at the top left of the screen and the positive y-axis points downwards.
    switch (e.code) {
    case 0: // x-axis, - left, + right.
        ev.type.m = In::MType::X;
        ev.val.min.x = e.value;
        break;
    case 1: // y-axis, - upwards, + downwards.
        ev.type.m = In::MType::Y;
        ev.val.min.y = e.value;
        break;
    case 8: // wheel scroll.
        ev.type.m = In::MType::Wheel;
        ev.val.min.wheel = e.value;
        break;
    }
}

// Absolute value to announce touch pad movement speed?
static void abs(In::Evt& ev, input_event& e) {
    //cout << "EV_ABS: " << e.value << endl;
}

// Handle synthetic events.
static void syn(In::Evt& ev, input_event& e) {
    switch (e.code) {
    case SYN_REPORT:
        break;
    case SYN_DROPPED: // Oh snap!
        break; // TODO: Throw away all frames between the reports.
    }
}

// Fill in event based on its read type.
static bool fill(In::Evt& ev, input_event& e) {
    switch (e.type) {
    case EV_REL: // Relative motion.
        rel(ev, e);
        return true;
    case EV_KEY: // Mouse button press and release.
        key(ev, e);
        return true;
    case EV_SYN: // Synthetic events.
        syn(ev, e);
        return false;
    case EV_ABS: // Absolute motion.
        //abs(ev, e);
        return false;
    case EV_MSC: // Miscellanous?
        return false;
    default:
        //cout << "Unknown type:" << hex << setw(2) << e.type << endl;
        break;
    }
    throw err("Unknown type!");
}

// Read mouse event device file.
static void evtrd(In::Evt& ev, const int fd) {
    input_event e;
    ssize_t ret;
    do {
        ret = ::read(fd, &e, sizeof e);
        if (ret == -1) // error.
            throw errno; // todo.
        if (ret == 0) // finished.
            break;
        if (fill(ev, e))
            break;
    } while (ret > 0);
}

// Read generic mouse file.
static void mrd(In::Evt& ev, const int fd) {
    // Read using generic mouse device file.
    char e[3], x, y;
    int left, mid, right, wheel;
    const auto ret = ::read(fd, &e, sizeof e);
    if (ret == -1)
        throw errno; // todo.
    if (ret == 0)
        return;
    if (ret == sizeof e) {
        ev.type.m = In::MType::Left;
        ev.val.min.left  = e[0] & 1;        // 1 bit is left mouse button pressed?
        ev.val.min.right = (e[0] >> 1) & 1; // 2 bit is right mouse button pressed?
        ev.val.min.mid   = (e[0] >> 2) & 1; // 3 bit is middle mouse button pressed?
        ev.val.min.x     = e[1];            // x.
        ev.val.min.y     = e[2];            // y.
        return;
    }
    throw ("Error reading /dev/input/mouse0");
}

// Read mouse input from mouse device file
In::Evt In::read() {
    Evt ev;
    zero(ev);
    ev.d = In::Dev::Mouse;
    goto skip;
    // Is using event-drive mouse device file?
    if (evt) {
        evtrd(ev, fd);
        return ev;
    }
skip:
    mrd(ev, fd);
    return ev;
}
