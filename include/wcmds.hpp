#pragma once
#include "types.hpp"

// Window commands/opcodes.
enum wndcmd : s8 {
    max,   // User wants to maximize window.
    min,   // User wants to minimize window.
    click, // User clicks somewhere on the window.
    copy,  // User wants to copy an existing rectangular image to a window. Sends a raw or compressed rectangular image. User chooses driver.
};
