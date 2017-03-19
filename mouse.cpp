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
    const char GENERIC[] = "Generic mouse";
    const char *evtp = "/dev/input/event0"; // File path to the event-driven mouse device file.
    const char *mp   = "/dev/input/mouse0"; // File path to the generic mouse input device file.
}

// Discover mouse event file.
static int discover() {
    int fd, n = 3;
    stringstream ss;
    for (int i = 0; i < n; ++i) {
        ss << "/dev/input/event" << i;
        if ((fd = ::open(ss.str().c_str(), O_RDONLY) != -1))
            return fd;
        ss.str("");
    }
    throw err("No mouse found!");
}

// Open mouse input device file.
Mouse::Mouse() {
    stringstream ss;
    // Event-driven mouse input using event files.
    if ((fd = ::open(evtp, O_RDONLY)) != -1) {
        path = evtp;
        isevt = true;
        cout << "Event mouse" << endl;
        return;
    }
    ss << "Cannot open " << evtp << ": " << strerror(errno);
    error(ss.str());
    // Generic mouse input using mouse0 device file.
    if ((fd = ::open(mp, O_RDONLY)) != -1) {
        path = mp; 
        isevt = false;
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
    if (isevt) {
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

// Handle left mouse button press.
static void left(const __s32 val) {
    cout << "Left: ";
    switch (val) {
    case 0:  // Released button.
        cout << "Released!" << endl;
        break;
    case 1:  // Pressed button.
        cout << "Pressed!" << endl;
        break;
    default: // Unknown value.
        cout << "Unknown " << val << endl;
        break;
    }
}

// Handle right mouse button press.
static void right(const __s32 val) {
    cout << "Right: ";
    switch (val) {
    case 0: // Released button.
        cout << "Released!" << endl;
        break;
    case 1: // Pressed button.
        cout << "Pressed!" << endl;
        break;
    default:
        cout << "Unknown " << val << endl;
        break;
    }
}

// Handle middle mouse button press.
static void middle(const __s32 val) {
    cout << "Middle: ";
    switch (val) {
    case 0: // Released button.
        cout << "Released!" << endl;
        break;
    case 1: // Pressed button.
        cout << "Pressed!" << endl;
        break;
    default:
        cout << "Unknown " << val << endl;
        break;
    }
}

// Handle side mouse button press.
static void side(const __s32 val) {
    cout << "Side: " << val << endl;
}

// X move mouse.
static void xmove(const __s32 val) {
    cout << " move: " << val << endl;
}

// Y move mouse.
static void ymove(const __s32 val) {
    cout << " move: " << val << endl;
}

// Back button on web browser.
static void back(const __s32 val) {
    cout << "back" << endl;
}

// Forward mouse button.
static void forward(const __s32 val) {
    cout << "forward" << endl;
}

// Extra mouse button.
static void extra(const __s32 val) {
}

// Task mouse button.
static void task(const __s32 val) {
}

// Mouse button press or release.
static void key(const __u16 code, const __s32 val) {
    cout << "EV_KEY: ";
    switch (code) {
    case BTN_LEFT:
        left(val);
        break;
    case BTN_RIGHT:
        right(val);
        break;
    case BTN_MIDDLE:
        middle(val);
        break;
    case BTN_SIDE:
        side(val);
        break;
    case BTN_EXTRA:
        extra(val);
        break;
    case BTN_FORWARD:
        forward(val);
        break;
    case BTN_BACK:
        back(val);
        break;
    case BTN_TASK:
        task(val);
        break;
    }
}

// Mouse scrolling.
static void scroll(const __s32 val) {
    switch (val) {
    case 1:  // up
        cout << "scroll up" << endl;
        break;
    case -1: // down
        cout << "scroll down" << endl;
        break;
    }
}

// This is mouse movement.
static void rel(const __u16 code, const __s32 val) {
    cout << "EV_REL: ";
    // Mouse movements follows top-left coordinate system, 
    // where origo is at the top left of the screen and the positive y-axis points downwards.
    switch (code) {
    case 0: // x-axis, - left, + right.
        cout << "x: ";
        xmove(val);
        break;
    case 1: // y-axis, - upwards, + downwards.
        cout << "y: ";
        ymove(val);
        break;
    case 8: // scroll.
        scroll(val);
        break;
    default:
        cout << "unknown " << code;
        break;
    }
}

// Read mouse event device file.
static void evtrd(const int fd) {
    input_event e;
    while (::read(fd, &e, sizeof e)) {
        switch (e.type) {
        case EV_SYN: // Synthetic events.
            cout << "EV_SYN: " << e.value << endl;
            break;
        case EV_REL: // Relative motion.
            rel(e.code, e.value);
            break;
        case EV_ABS: // Absolute motion.
            cout << "EV_ABS: " << e.value << endl;
            break;
        case EV_KEY: // Mouse button press and release.
            key(e.code, e.value);
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
void Mouse::read() {
    // Is using event-drive mouse device file?
    if (isevt) {
        evtrd(fd);
        return;
    }
    // Read using generic mouse device file.
    char e[4], x, y;
    int left, mid, right, wheel;
    while (::read(fd, &e, sizeof e)) {
        left  = e[0] & 1;        // 1 bit is left mouse button pressed?
        right = (e[0] >> 1) & 1; // 2 bit is right mouse button pressed?
        mid   = (e[0] >> 2) & 1; // 3 bit is middle mouse button pressed?
        x     = e[1];
        y     = e[2];
        wheel = e[3]; // mouse wheel change.
        printf("x=%d, y=%d, left=%d, middle=%d, right=%d, wheel=%d\n", x, y, left, mid, right, wheel);
    }
}
