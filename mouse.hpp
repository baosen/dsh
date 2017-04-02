#pragma once
#include <string>
#include <queue>
#include "types.hpp"

// "Hacky" mouse device input file.
class Mouse {
public:
    // Input event.
    struct Evt {
        int  x, y;             // x and y cartesian movement.
        bool left, right, mid; // Left, middle and right pressed or released mouse buttons.
    };

    // Claims the ith mouse input device.    
    Mouse(const uint i);
    // Releases the mouse input device.    
    ~Mouse();

    // Waits for mouse event and reads it.
    Evt rd();
private:
    int fd;   // mouse input device file descriptor.
};
