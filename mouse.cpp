#include <iostream>
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
        return;
    }
    ss << "Cannot open " << path << ": " << strerror(errno);
    error(ss.str());
    // Generic mouse input using mouse0 device file.
    if ((fd = ::open(mp, O_RDONLY)) != -1) {
        path = mp; 
        isevt = false;
        return;
    }
    ss.str("");
    ss << "Cannot open " << path << ": " << strerror(errno);
    error(ss.str());
}

// Close mouse input device file.
Mouse::~Mouse() {
    stringstream ss;
    if (::close(fd) == -1) {
        ss << "Cannot close " << path << ": " << strerror(errno);
        die(ss.str().c_str());
    }
}

void evtrd(const int fd) {
    input_event e;
    while (::read(fd, &e, sizeof e)) {
        switch (e.type) {
        case EV_SYN:
            cout << "EV_SYN" << endl;
            break;
        case EV_REL:
            cout << "EV_REL" << endl;
            break;
        case EV_ABS:
            cout << "EV_REL" << endl;
            break;
        default:
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