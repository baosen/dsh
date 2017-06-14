#include "ev.hpp"

// Mouse input from mouse event device file.
class Evm {
public:
    Evm();
    // Open event device file for mouse.
    Evm(const uint i);
    // Read input event from the mouse event device.
    input_event rd();
private:
    Ev ev;
};
