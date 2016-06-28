#include <unistd.h>
#include <fcntl.h>
#include "mouse.hpp"

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
