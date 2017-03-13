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
    const char *evtp = "/dev/input/event0"; // File path to the event-driven mouse device file.
    const char *mp   = "/dev/input/mouse0"; // File path to the generic mouse input device file.
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
        cout << "Generic mouse" << endl;
        return;
    }
    ss.str("");
    ss << "Cannot open " << mp << ": " << strerror(errno);
    error(ss.str());
    exit(1);
}

// Close mouse input device file.
Mouse::~Mouse() {
    stringstream ss;
    if (::close(fd) == -1) {
        ss << "Cannot close " << path << ": " << strerror(errno);
        die(ss.str().c_str());
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
            cout << "EV_REL: " << e.value << endl;
            break;
        case EV_ABS: // Absolute motion.
            cout << "EV_ABS: " << e.value << endl;
            break;
        case EV_KEY: // Mouse button press and release.
            cout << "EV_KEY: " << e.value << endl;
            break;
        case EV_MSC: // Miscellanous?
            cout << "EV_MSC: " << e.value << endl;
            break;
        default:
            cout << "Unknown type:" << hex << setw(2) << e.type << endl;
            break;
        }
        cout << "Code: " << e.code << endl;
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