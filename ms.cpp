#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include "mouse.hpp"
using namespace std;

namespace {
    const char *path = "/dev/input/mouse2";
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

input_event Mouse::read() {
    input_event e;
    while (::read(fd, &e, sizeof e))
        printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n", e.time.tv_sec, e.time.tv_usec, e.type, e.code, e.value);
    return e;
}
