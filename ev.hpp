#pragma once
#include <linux/input.h>
#include "types.hpp"

// Event-driven input using event* device file.
class Ev {
public:
    // Create empty event input device file.
    Ev();
    // Open event device file.
    Ev(const uint i);

    // Read from event file.
    input_event rd();

    // Get event bits.
    void evbits(char*);

    // Close event device file.
    ~Ev();
private:
    int fd; // event device file descriptor.
};
