#pragma once
#include <string>
#include <tuple>

class Mouse {
    std::string path; // file path to device file.
    int fd;           // mouse input device file descriptor.
    bool isevt;       // is using event file.
public:
    // Mouse event made by the user.
    enum class Evt {
        LEFT,  // Left mouse button press or release.
        RIGHT, // Right mouse button press or release.
        MID,   // Middle mouse button press or release.
        SCR,   // Up and down mouse scroll.
        X,     // Movement of x-axis.
        Y,     // Movement of y-axis.
    };

    // Mouse-wheel scroll.
    enum Scr {
        UP   = 1,  // Scroll upwards.
        DOWN = -1, // Scroll downwards.
    };

    // Claims the mouse.    
    Mouse();

    // Releases the mouse.    
    ~Mouse();

    // Waits for mouse event and reads it.
    std::tuple<Mouse::Evt, int> read();

    // Returns the name of the mouse device.
    std::string name();
};
