#include "wcmds.hpp"

// Do window command.
int wndcmd(const int cmd) 
{
    switch (cmd) {
    case Wndcmd::max:   // User wants to maximize window.
        return 0;
    case Wndcmd::min:   // User wants to minimize window.
        return 0;
    case Wndcmd::click: // User clicks somewhere on the window.
        return 0;
    case Wndcmd::copy:  // User wants to copy an existing rectangular image to a window. Sends a raw or compressed rectangular image. User chooses driver.
        return 0;
    default:
        break;
    }
    return -EINVAL;
}
