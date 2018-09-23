#include "ev.hpp"

// Mouse input from mouse event device file.
class evm {
public:
    evm();
    // Open event device file for mouse.
    evm(const uint i);

    // Open mouse event device file.
    bool open(const uint i);
    // Close mouse event device file.
    void close();

    // Read input event from the mouse event device.
    input_event rd();
private:
    ev e;
};
