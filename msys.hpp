// Mouse subsystem.
#pragma once
#include "pos.hpp"

namespace msys {
    // Initialize and setup mouse.
    void init();

    // Gets the position of the mouse.
    typedef Pos (*Mposf)();

    // Current mouse device that is used.
    extern Mposf mcurpos;
}
