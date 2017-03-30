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

// Open input device file.
Ms::Ms(const char *path) : oldl(false), oldr(false), oldm(false) {
    stringstream ss;
    // Generic input using mouse* device file.
    if (strstr(path, "mouse")) {
        if ((fd = ::open(path, O_RDONLY)) != -1) {
            this->path = path;
            return;
        } 
    } 
    ss << "Cannot open " << path << ": " << strerror(errno);
    error(ss.str());
    throw err("Failed to open input device!");
}

// Close mouse input device file.
Ms::~Ms() {
    stringstream ss;
    if (::close(fd) == -1) {
        ss << "Cannot close " << path << ": " << strerror(errno);
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
        evmk(d, e);
        return;
    }
    throw ("Error reading /dev/input/mouse0");
}
