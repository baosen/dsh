#include <linux/input.h>

// Mouse input device.
class Mouse {
public:
    // Input event.
    struct Evt {
        int  x, y;             // x and y cartesian movement.
        bool left, mid, right, // Left, middle and right pressed or released mouse buttons.
        int  wheel;            // Wheel scroll.
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

    // Open event device file for mouse.
    Mouse(Evt&);

    // Read mouse event.
    Mouse::Evt rd();
private:
    bool oldl, // Old left button value.
         oldr, // Old right button value.
         oldm; // Old middle button value.
};
