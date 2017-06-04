// Mouse subsystem.
#pragma once
#include "pos.hpp"

// Initialize and setup mouse.
void initm();

// Gets the position of the mouse.
typedef Pos (*Mposf)();

// Current mouse device that is used.
extern Mposf mcurpos;
