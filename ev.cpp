#include <sstream>
#include <cstring>
#include "fio.hpp"
#include "log.hpp"
#include "ev.hpp"
#include "err.hpp"
using namespace std;

// Create empty event input device file.
Ev::Ev() : fd(-2) {}

// Open event device file.
Ev::Ev(const uint i) {
    // Try opening the event device file.
    stringstream ss;
    ss << "/dev/input/event" << i;
    if ((fd = ::open(ss.str().c_str(), O_RDONLY)) != -1)
        return;
    // Throw opening failure error.
    string s(ss.str());
    ss.str("");
    ss << "Cannot open event device file " << s << ": " << strerror(errno);
    throw err(ss.str());
}

// Close event device file.
Ev::~Ev() {
    // If no event device file is opened yet.
    if (fd == -2)
        return;
    // Try closing event device file.
    stringstream ss;
    if (::close(fd) == -1) {
        ss << "Cannot close event device file: " << strerror(errno);
        die(ss.str().c_str());
    }
}

// Get event bits.
void Ev::evbits(char b[EV_MAX]) {
    int n;
    if ((n = ioctl(fd, EVIOCGBIT(0, EV_MAX), b)) < 0)
        throw err("Could not get event types.");
}

// Read from event file.
input_event Ev::rd() {
    input_event e;
    if (::read(fd, &e, sizeof e) < 0) {
        stringstream ss;
        ss << "Failed to read event file: " << strerror(errno) << endl;
        throw err(ss.str());
    }
    return e;
}
