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
        LEFTPRS,  // Left mouse button press.
        RIGHTPRS, // Right mouse button press.
        LEFTRLS,  // Left mouse button release.
        RIGHTRLS, // Right mouse button release.
        UPSCR,    // Up mouse scroll.
        DOWNSCR,  // Down mouse scroll.
        XLEFT,    // Movement to the left of x-axis.
        XRIGHT,   // Movement to the right of x-axis.
        YUP,      // Movement upwards the y-axis.
        YDOWN,    // Movement downards the y-axis.
    };
    Mouse();
    ~Mouse();
    std::tuple<Mouse::Evt, int> read();
    std::string name();
};
