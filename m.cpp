#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include "zero.hpp"
#include "log.hpp"
#include "m.hpp"
using namespace std;

// Open mouse input device file.
M::M(const uint i) {
    stringstream ss;
    // Generic input using mouse* device file.
    ss << "/dev/input/mouse" << i;
    if ((fd = ::open(ss.str().c_str(), O_RDONLY)) != -1)
        return;
    string s(ss.str());
    ss.str("");
    ss << "Cannot open " << s << ": " << strerror(errno);
    throw err(ss.str());
}

// Close mouse input device file.
M::~M() {
    stringstream ss;
    if (::close(fd) == -1) {
        ss << "Cannot close mouse input device file: " << strerror(errno);
        die(ss.str().c_str());
    }
}

// Read mouse input from mouse device file.
M::Evt M::rd() {
    // Read using generic mouse device file.
    char e[3];
    const auto ret = ::read(fd, &e, sizeof e);
    if (ret == -1)
        throw errno; // todo.
    if (ret == sizeof e) {
        M::Evt ev;
        ev.x     = e[1];              // x.
        ev.y     = e[2];              // y.
        ev.left  = (e[0] & 1);        // 1 bit is left mouse button pressed?
        ev.right = ((e[0] >> 1) & 1); // 2 bit is right mouse button pressed?
        ev.mid   = ((e[0] >> 2) & 1); // 3 bit is middle mouse button pressed?
        return ev;
    }
    throw ("Error reading /dev/input/mouse0");
}
