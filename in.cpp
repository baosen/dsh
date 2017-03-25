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
    const char evtp[] = "/dev/input/event0"; // File path to the event-driven mouse device file.
    const char mp[]   = "/dev/input/mouse0"; // File path to the "hacky" generic mouse input device file.
}

// Return number of device files.
static uint nfiles() {
    return 3;
}

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
    throw err("No generic mouse found!");
}

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
    throw err("No event mouse found!");
}

// Open input device file.
In::In() : oldl(false), oldr(false), oldm(false) {
    stringstream ss;
    // Event-driven input using event* device file.
    if ((fd = ::open(evtp, O_RDONLY)) != -1) {
        path = evtp;
        evt = true;
        //cout << "Event mouse" << endl;
        return;
    }
    ss << "Cannot open " << evtp << ": " << strerror(errno);
    error(ss.str());
    // Generic input using mouse* device file.
    if ((fd = ::open(mp, O_RDONLY)) != -1) {
        path = mp; 
        evt = false;
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
    return mp;
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
        ev.val.min.extra = e.value;
        break;
    case BTN_FORWARD: // Forward button.
        ev.type.m = In::MType::Forward;
        ev.val.min.forward = e.value;
        break;
    case BTN_BACK:    // Back button (to go backwards in browser?).
        ev.type.m = In::MType::Back;
        ev.val.min.back = e.value;
        break;
    case BTN_TASK:    // Task button.
        ev.type.m = In::MType::Task;
        ev.val.min.task = e.value;
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
//static void abs(In::Evt& ev, input_event& e) {
//}

// Handle synthetic events.
static bool syn(In::Evt& ev, const __s32 code) {
    switch (code) {
    case SYN_REPORT:
        return true;
    case SYN_DROPPED: // Oh snap!
        break;
    }
    return false; // TODO: Throw away all frames between the reports.
}

// Fill in event based on its read type.
static bool fill(deque<In::Evt>& d, input_event& e) {
    In::Evt ev;
    zero(ev);
    ev.d = In::Dev::Mouse;
    switch (e.type) {
    case EV_REL: // Relative motion.
        rel(ev, e);
        d.push_back(ev);
        return false;
    case EV_KEY: // Mouse button press and release.
        key(ev, e);
        d.push_back(ev);
        return false;
    case EV_ABS: // Absolute motion.
        return false;
    case EV_MSC: // Miscellanous?
        return false;
    case EV_SYN: // Synthetic events.
        return syn(ev, e.code);
    default:
        //cout << "Unknown type:" << hex << setw(2) << e.type << endl;
        throw err("Unknown type!");
    }
}

// Read mouse event device file.
static void evtrd(deque<In::Evt>& d, const int fd) {
    input_event e;
    ssize_t ret;
    do {
        ret = ::read(fd, &e, sizeof e);
        if (ret == -1)   // error.
            throw errno; // todo.
        if (ret == 0)    // finished reading.
            break;
        if (fill(d, e))
            break;
    } while (ret > 0);
}

// Make event.
void In::evmk(deque<In::Evt>& d, char e[3]) {
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
    if (oldm != m) {
        ev.type.m = In::MType::Mid;
        oldm = ev.val.min.mid = m;
        d.push_back(ev);
    }
    // Add mouse movement events. 
    // Add X movement.
    ev.type.m = In::MType::X;
    ev.val.min.x = e[1]; // x.
    d.push_back(ev);
    // Add Y movement. Y is flipped here!
    ev.type.m = In::MType::Y;
    ev.val.min.y = e[2]*-1; // y.
    d.push_back(ev);
}

// Read generic mouse file.
void In::mrd(deque<In::Evt>& d, const int fd) {
    // Read using generic mouse device file.
    char e[3];
    const auto ret = ::read(fd, &e, sizeof e);
    if (ret == -1)
        throw errno; // todo.
    if (ret == 0)
        return;
    if (ret == sizeof e) {
        evmk(d, e);
        return;
    }
    throw ("Error reading /dev/input/mouse0");
}

// Read mouse input from mouse device file
deque<In::Evt> In::read() {
    deque<In::Evt> d;
    // Is using event-drive mouse device file?
    if (evt) {
        evtrd(d, fd);
        goto exit;
    }
    mrd(d, fd);
exit:
    return d;
}
