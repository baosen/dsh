#pragma once
#include <string>
#include <queue>
#include "types.hpp"

// "Hacky" mouse device input file.
class M {
public:
    // Mouse-wheel scroll.
    enum Scr {
        UP   = 1,  // Scroll upwards.
        DOWN = -1, // Scroll downwards.
    };

    // Mouse input event.
    struct Ev {
        int  x, y;             // x and y cartesian movement.
        bool left, mid, right; // Left, middle and right pressed or released mouse buttons.
    };

    // Create a empty "hacky" mouse.
    M();
    // Claims the ith mouse input device.    
    M(const uint i);
    // Releases the mouse input device.    
    ~M();

    // Open "hacky" mouse.
    bool open(const uint i);
    // Close "hacky" mouse.
    void close();

    // Waits for mouse event and reads it.
    Ev rd();
private:
    int fd;   // mouse input device file descriptor.
};
