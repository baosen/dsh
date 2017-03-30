#include <linux/input.h>

// Mouse input device.
class Mouse {
public:
    // Input event.
    struct Evt {
        __u16 type;
        struct {                   
            int  x, y;             // x and y cartesian movement.
            bool left, mid, right, // Left, middle and right pressed or released mouse buttons.
            int  wheel;            // Wheel scroll.
        } min;                     // Mouse input.
        __s32 val;
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
    deque<Mouse::Evt> Mouse::rd();
private:
    bool oldl, // Old left button value.
         oldr, // Old right button value.
         oldm; // Old middle button value.
};
