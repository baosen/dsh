#pragma once
#include "types.hpp"

// Display commands/operations.
enum Dpycmd : u8 {
    reset, // Reset the display.
    res,   // Set screen resolution.
    hz,    // Set screen hertz.
};
