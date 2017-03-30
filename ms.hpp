#pragma once
#include <string>
#include <queue>
#include "types.hpp"

// "hacky" mouse device input file.
class Ms {
public:
    // Claims the ith mouse input device.    
    Ms(const uint i);
    // Releases the mouse input device.    
    ~Ms();

    // Waits for mouse event and reads it.
    std::deque<In::Evt> rd();
private:
    int  fd;   // mouse input device file descriptor.
    bool evt;  // is using event file.
};
