#include <sstream>
#include "fio.hpp"
#include "zero.hpp"
#include "log.hpp"
#include "m.hpp"
using namespace std;

// Open an empty "hacky" mouse.
m::m() 
    : fd(-2) 
{}

// Open the "hacky" mouse input device file.
m::m(const uint i) 
{
    // Open mouse i.
    if (open(i))
        return;

    // Generic input using mouse* device file.
    stringstream ss;
    ss << "/dev/input/mouse" << i;
    string s(ss.str());
    ss << "Cannot open hacky mouse file " << s << ": " << strerror(errno);
    throw err(ss.str());
}

// Close mouse input device file.
m::~m() 
{
    close();
}

// Open "hacky" mouse.
bool m::open(const uint i) 
{
    // Generic input using mouse* device file.
    stringstream ss;
    ss << "/dev/input/mouse" << i;
    return (fd = ::open(ss.str().c_str(), O_RDONLY)) != -1;
}

// Close "hacky" mouse.
void m::close() 
{
    // If empty "hacky" mouse.
    if (fd == -2)
        return;
    // Close "hacky" mouse file.
    stringstream ss;
    if (::close(fd) < 0) {
        ss << "Cannot close hacky mouse device file: " << strerror(errno);
        // TODO!
        die(ss.str().c_str());
    }
}

// Read mouse input from mouse device file.
m::ev m::rd() 
{
    // Read using generic mouse device file.
    char       e[3]; // The read mouse state.
    const auto ret = ::read(fd, &e, sizeof e);

    // Failed to read?
    if (ret < 0)
        throw errno; // todo.
    if (ret == sizeof e) {
        m::ev evt;
        evt.x     = e[1];              // x.
        evt.y     = e[2];              // y.
        evt.left  = (e[0] & 1);        // 1 bit is left mouse button pressed?
        evt.right = ((e[0] >> 1) & 1); // 2 bit is right mouse button pressed?
        evt.mid   = ((e[0] >> 2) & 1); // 3 bit is middle mouse button pressed?
        return evt;
    }
    throw err("Error reading /dev/input/mouse0");
}
