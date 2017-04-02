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

    // Button state
    enum Btn {
        RLS, // Released.
        PRS  // Pressed.
    };

    // Mouse input event.
    struct Ev {
        int  x, y;             // x and y cartesian movement.
        bool left, right, mid; // Left, middle and right pressed or released mouse buttons.
    };

    // Claims the ith mouse input device.    
    M(const uint i);
    // Releases the mouse input device.    
    ~M();

    // Waits for mouse event and reads it.
    Ev rd();
private:
    int fd;   // mouse input device file descriptor.
};
