#pragma once
#include <cstring>
#include "types.hpp"

// Mouse subsystem.
namespace msys {
    // Mouse event.
    struct Ev {
        // Type of mouse event.
        enum {
            X,       // X motion.
            Y,       // Y motion.
            WHEEL,   // Wheel scroll.
            LEFT,    // Left button.
            MID,     // Middle button.
            RIGHT,   // Right button.
            UPSCR,   // Upwards scroll of scroll button.
            DOWNSCR, // Downward scroll of scroll button.
            SIDE,    // Side button.
            EXTRA,   // Extra button.
            FORWARD, // Forward button.
            BACK,    // Back button.
            TASK,    // Task button.
        } type;
        // Data describing the event.
        // Mouse move in the mirrored y cartesian axis. 
        // Y-axis is mirrored to act the same as the axis of a framebuffer usually found in graphical devices.
        int val;
        // a move in the x-axis where towards the right is positive and towards the left is negative.
        // a move in the y-axis where towards the bottom is positive (+) and towards the top is negative (-).
        // Up scroll is 1. Down scroll is -1.
    };

    // Initialize and setup mouse.
    void init();
    // Deinitialize and setup mouse.
    void deinit();

    // Wait for event and get mouse motion.
    typedef uint (*Mmotion)(void *buf, const size_t n);

    // Current mouse device that is used.
    extern Mmotion getmot;
}
