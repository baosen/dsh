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

// Open mouse input device file.
Ms::Ms(const uint i) {
    stringstream ss;
    // Generic input using mouse* device file.
    ss << "/dev/input/mouse" << i;
    const auto path = ss.str().c_str();
    if ((fd = ::open(path, O_RDONLY)) != -1)
        return;
    ss << "Cannot open " << path << ": " << strerror(errno);
    error(ss.str());
    throw err("Failed to open input device!");
}

// Close mouse input device file.
Ms::~Ms() {
    stringstream ss;
    if (::close(fd) == -1) {
        ss << "Cannot close mouse input device file: " << strerror(errno);
        die(ss.str().c_str());
    }
}

// Read mouse input from mouse device file.
Mouse::Evt Ms::rd() {
    // Read using generic mouse device file.
    char e[3];
    const auto ret = ::read(fd, &e, sizeof e);
    if (ret == -1)
        throw errno; // todo.
    if (ret == sizeof e) {
        Mouse::Evt e;
        e.x     = e[1];              // x.
        e.y     = e[2];              // y.
        e.left  = (e[0] & 1);        // 1 bit is left mouse button pressed?
        e.right = ((e[0] >> 1) & 1); // 2 bit is right mouse button pressed?
        e.mid   = ((e[0] >> 2) & 1); // 3 bit is middle mouse button pressed?
        return e;
    }
    throw ("Error reading /dev/input/mouse0");
}
