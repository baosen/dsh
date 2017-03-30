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
void Ms::rd(deque<In::Evt>& d, const int fd) {
    // Read using generic mouse device file.
    char e[3];
    const auto ret = ::read(fd, &e, sizeof e);
    if (ret == -1)
        throw errno; // todo.
    if (ret == 0)
        return;
    if (ret == sizeof e) {
        mk(d, e);
        return;
    }
    throw ("Error reading /dev/input/mouse0");
}
