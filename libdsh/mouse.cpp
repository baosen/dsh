#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include "mouse.hpp"
using namespace std;

namespace {
    const char *path = "/dev/input/mouse0";
    int fd;
}

Mouse::Mouse() {
    fd = ::open(path, O_RDONLY);
    if (fd == -1) {
        cerr << "Cannot open " << path << ": " << strerror(errno) << endl;
        exit(1);
    }
}

Mouse::~Mouse() {
    if (::close(fd) == -1) {
        cerr << "Cannot close " << path << ": " << strerror(errno) << endl;
        exit(1);
    }
}

void Mouse::read() {
    char e[4], x, y;
    int left, mid, right, wheel;
    while (::read(fd, &e, sizeof e)) {
        left = e[0] & 1; // 1 bit is left mouse button.
        right = (e[0] >> 1) & 1; // 2 bit is right mouse button.
        mid = (e[0] >> 2) & 1; // 3 bit is middle mouse button.
        x = e[1];
        y = e[2];
        wheel = e[3];
        printf("x=%d, y=%d, left=%d, middle=%d, right=%d, wheel=%d\n", x, y, left, mid, right, wheel);
    }
}
