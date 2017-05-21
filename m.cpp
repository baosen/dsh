#include <sstream>
#include "fio.hpp"
#include "zero.hpp"
#include "log.hpp"
#include "m.hpp"
using namespace std;

// Open an empty "hacky" mouse.
M::M() : fd(-2) {}

// Open the "hacky" mouse input device file.
M::M(const uint i) {
    if (open(i))
        return;
    // Generic input using mouse* device file.
    stringstream ss;
    ss << "/dev/input/mouse" << i;
    string s(ss.str());
    ss << "Cannot open " << s << ": " << strerror(errno);
    throw err(ss.str());
}

// Close mouse input device file.
M::~M() {
    // If empty "hacky" mouse.
    if (fd == -2)
        return;
    stringstream ss;
    if (::close(fd) == -1) {
        ss << "Cannot close mouse input device file: " << strerror(errno);
        die(ss.str().c_str());
    }
}

// Open "hacky" mouse.
bool M::open(const uint i) {
    // Generic input using mouse* device file.
    stringstream ss;
    ss << "/dev/input/mouse" << i;
    return (fd = ::open(ss.str().c_str(), O_RDONLY)) != -1;
}

// Read mouse input from mouse device file.
M::Ev M::rd() {
    // Read using generic mouse device file.
    char e[3];
    const auto ret = ::read(fd, &e, sizeof e);
    if (ret == -1)
        throw errno; // todo.
    if (ret == sizeof e) {
        M::Ev ev;
        ev.x     = e[1];              // x.
        ev.y     = e[2];              // y.
        ev.left  = (e[0] & 1);        // 1 bit is left mouse button pressed?
        ev.right = ((e[0] >> 1) & 1); // 2 bit is right mouse button pressed?
        ev.mid   = ((e[0] >> 2) & 1); // 3 bit is middle mouse button pressed?
        return ev;
    }
    throw err("Error reading /dev/input/mouse0");
}
