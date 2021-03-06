#include <sstream>
#include <cstring>
#include "fio.hpp"
#include "log.hpp"
#include "ev.hpp"
#include "err.hpp"
using namespace std;

// Create empty event input device file.
ev::ev() : fd(-2) {}

// Open event device file.
ev::ev(const uint i) 
{
    open(i);
}

// Close event device file.
ev::~ev() 
{
    close();
}

// Open device file.
bool ev::open(const uint i) 
{
    // Try opening the event device file.
    stringstream ss;
    ss << "/dev/input/event" << i;
    // Open event* file.
    if ((fd = ::open(ss.str().c_str(), O_RDONLY)) != -1)
        return true; // Succeeded opened.
    // Throw opening failure error.
    string s(ss.str());
    ss.str("");
    ss << "Cannot open event device file " << s << ": " << strerror(errno);
    throw err(ss.str());
}

// Close device file.
void ev::close() 
{
    // If no event device file is opened yet.
    if (fd == -2)
        return;

    // Try closing event device file.
    if (::close(fd) < 0) { // BUG: I'm getting bad file descriptor here.
        stringstream ss;
        ss << "Cannot close event device file: " << strerror(errno);
        // TODO!
        die(ss.str().c_str());
    }
}

// Get event bits.
void ev::evbits(char b[EV_MAX]) 
{
    int n;
    if ((n = ioctl(fd, EVIOCGBIT(0, EV_MAX), b)) < 0)
        throw err("Could not get event types.");
}

// Read from event file.
input_event ev::rd() 
{
    input_event e;

    if (::read(fd, &e, sizeof e) < 0) {
        stringstream ss;
        ss << "Failed to read event file: " << strerror(errno) << endl;
        throw err(ss.str());
    }

    return e;
}
