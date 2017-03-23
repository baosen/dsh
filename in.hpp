#pragma once
#include <string>
#include <tuple>

// Class In;
// class Out;
class In {
    std::string path; // file path to device file.
    int         fd;   // mouse input device file descriptor.
    bool        evt;  // is using event file.
public:
    // Mouse event type made by the user.
    enum class MType {
        LEFT,    // Left mouse button press or release.
        RIGHT,   // Right mouse button press or release.
        MID,     // Middle mouse button press or release.
        SIDE,    // Side mouse button press or release.
        EXTRA,   // Extra mouse button press or release.
        FORWARD, // Forward mouse button press or release.
        BACK,    // Back mouse button press or release.
        TASK,    // Task mouse button press or release.
        SCR,     // Up and down mouse scroll.
        X,       // Movement of x-axis.
        Y,       // Movement of y-axis.
    };

    enum Dev {
        MOUSE,
        TPAD,
        TSCR,
    };

    // Mouse event made by the user.
    struct Evt {
        Dev dev;
        Type type;
        union {
            struct {
                int x, y;              // movement in the x and y coordinate system.
                bool left, mid, right; // left, middle and right button pressed or released..
                int wheel;             // wheel scroll.
            } in;
        } val;
    };

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

    // Claims the mouse.    
    In();
    // Releases the mouse.    
    ~In();

    // Waits for mouse event and reads it.
    Evt read();

    // Returns the name of the mouse device.
    std::string name();
};
