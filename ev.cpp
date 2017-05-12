#include <sstream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include "log.hpp"
#include "ev.hpp"
#include "err.hpp"
using namespace std;

// Create empty event input device file.
Ev::Ev() : fd(-2) {}

// Open event device file.
Ev::Ev(const uint i) {
    stringstream ss;
    ss << "/dev/input/event" << i;
    if ((fd = ::open(ss.str().c_str(), O_RDONLY)) != -1)
        return;
    string s(ss.str());
    ss.str("");
    ss << "Cannot open event device file " << s << ": " << strerror(errno);
    throw err(ss.str());
}

// Close event device file.
Ev::~Ev() {
    if (fd == -2)
        return;
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
    const ssize_t ret = ::read(fd, &e, sizeof e);
    if (ret < 0)   // error.
        throw errno; // todo.
    return e;
}
