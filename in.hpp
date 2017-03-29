#pragma once
#include <string>
#include <queue>

// Device input.
class In {
public:
    // Mouse event type made by the user.
    enum class MType {
        Left,    // Left mouse button press or release.
        Right,   // Right mouse button press or release.
        Mid,     // Middle mouse button press or release.
        Side,    // Side mouse button press or release.
        Extra,   // Extra mouse button press or release.
        Forward, // Forward mouse button press or release.
        Back,    // Back mouse button press or release.
        Task,    // Task mouse button press or release.
        Wheel,   // Up and down mouse wheel scroll.
        X,       // Movement of x-axis.
        Y,       // Movement of y-axis.
    };

    // Touch pad event type
    enum class TPadType {
        Pinch,
        Expand,
    };

    // Input device.
    enum class Dev {
        Mouse,   // Mouse.
        Tpad,    // Touchpad.
        Tscr,    // Touchscreen.
    };

    // Input event.
    struct Evt {
        // Input device.
        Dev d;                         // Tells what kind of input device that threw this event.

        // Input type.
        union {
            MType m;                   // Mouse type.
            TPadType t;                // Touchpad type.
        } type;                        // Type of input value.

        // Input value.
        union {                        // Input value.
            struct {                   
                int  x, y;             // x and y cartesian movement.
                // Pressed or released mouse buttons.
                bool left, mid, right, // Left, middle and right mouse buttons.
                     side, extra,      // Side and extra mouse buttons.
                     forward, back,    // Forward and back mouse buttons.
                     task;             // Task mouse button.
                int  wheel;            // Wheel scroll.
            } min;                     // Mouse input.
        } val;                         // The value given by the input device.
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

    bool oldl, // Old left button value.
         oldr, // Old right button value.
         oldm; // Old middle button value.

    // Claims the input device.    
    In(const char *path);
    // Releases the input device.    
    ~In();

    // Waits for mouse event and reads it.
    std::deque<In::Evt> rd();

    // Get event bits.
    void evbits(char*);

private:
    std::string path; // file path to input device.
    int         fd;   // mouse input device file descriptor.
    bool        evt;  // is using event file.

    void evmk(std::deque<In::Evt>& d, char e[3]);
    void mrd(std::deque<In::Evt>& d, const int fd);
};
