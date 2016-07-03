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

input_event Ms::read() {
    input_event e;
    while (::read(fd, &e, sizeof e))
        printf("type %d\tcode %d\tvalue %d\n", e.type, e.code, e.value);
    return e;
}
