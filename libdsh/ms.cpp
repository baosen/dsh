#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include "ms.hpp"
using namespace std;

namespace {
    const char *path = "/dev/input/mouse2";
    int fd;
}

Ms::Ms() {
    fd = ::open(path, O_RDONLY);
    if (fd == -1) {
        cerr << "Cannot open " << path << ": " << strerror(errno) << endl;
        exit(1);
    }
}

Ms::~Ms() {
    if (::close(fd) == -1) {
        cerr << "Cannot close " << path << ": " << strerror(errno) << endl;
        exit(1);
    }
}

void Ms::read() {
    char e[3], x, y;
    int left, mid, right;
    while (::read(fd, &e, sizeof e)) {
        left = e[0] & 1;
        mid = e[0] & 2;
        right = e[0] & 4;
        x = e[1];
        y = e[2];
        printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, mid, right);
    }
}
