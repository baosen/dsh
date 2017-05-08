#include "ev.hpp"

// Mouse input from mouse event device.
class Evm {
public:
    Evm();
    // Open event device file for mouse.
    Evm(const uint i);
    // Open event file.
    bool open(const uint i);
    int rd();
private:
    Ev ev;
};
