#include <linux/input.h>

// Mouse input device.
class Mouse {
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

    // Open event device file for mouse.
    Mouse(Evt&);
private:
    bool oldl, // Old left button value.
         oldr, // Old right button value.
         oldm; // Old middle button value.
};
