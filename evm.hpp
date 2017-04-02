#include "ev.hpp"

// Mouse input device.
class Evm {
public:
    // Open event device file for mouse.
    Evm();
    void rd();
private:
    Ev ev;
};
