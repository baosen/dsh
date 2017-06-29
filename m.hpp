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
        int x, // Movement in the X-axis of an cartesian coordinate system.
            y; // Movement in the Y-axis of an cartesian coordinate system.
        bool left,  // Is left button pressed or released?
             mid,   // Is middle button pressed or released?
             right; // Is right button pressed or released?
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
