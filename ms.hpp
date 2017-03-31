#pragma once
#include <string>
#include <queue>
#include "types.hpp"

// "hacky" mouse device input file.
class Ms {
public:
    // Input event.
    struct Evt {
        int  x, y;             // x and y cartesian movement.
        bool left, right, mid; // Left, middle and right pressed or released mouse buttons.
    };

    // Claims the ith mouse input device.    
    Ms(const uint i);
    // Releases the mouse input device.    
    ~Ms();

    // Waits for mouse event and reads it.
    Mouse::Evt rd();
private:
    int fd;   // mouse input device file descriptor.
};
