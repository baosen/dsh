// Mouse subsystem.
#pragma once
#include "pos.hpp"

namespace msys {
    // Mouse event.
    struct Ev {
        // Type of mouse event.
        enum {
            MOTION, // Motion event.
            PRS,    // Button is pressed.
            RLS,    // Button is released.
        } type;
        // Data describing the event.
        union {
            // Mouse move in the mirrored y cartesian axis. 
            // Y-axis is mirrored to act the same as the axis of a framebuffer usually found in graphical devices.
            struct {
                int x, // a move in the x-axis where towards the right is positive and towards the left is negative.
                    y; // a move in the y-axis where towards the bottom is positive (+) and towards the top is negative (-).
            } axis;
            // The button where an action was performed on.
            enum {
                LEFT,    // Left button.
                MID,     // Middle button.
                RIGHT,   // Right button.
                UPSCR,   // Upwards scroll of scroll button.
                DOWNSCR, // Downward scroll of scroll button.
            } btn;
        } data;
    };

    // Initialize and setup mouse.
    void init();

    // Gets the position of the mouse.
    typedef void (*Mposf)(void *buf);

    // Current mouse device that is used.
    extern Mposf pos;
}
