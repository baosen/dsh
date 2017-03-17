#pragma once
#include <string>

class Mouse {
    std::string path; // file path to device file.
    int fd;           // mouse input device file descriptor.
    bool isevt;       // is using event file.
public:
    Mouse();
    ~Mouse();
    void read();
    std::string name();
};
