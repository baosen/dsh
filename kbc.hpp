#pragma once
#include <linux/input.h>
#include "types.hpp"

// Convert keyboard code to ASCII character.
char    toc(const  __u16 c);
// Convert keyboard input event to ASCII character.
char    toc(const input_event& e);

// Convert keyboard code to Wide character.
wchar_t towc(const uint c);
// Convert keyboard input event to Wide character.
wchar_t towc(const input_event& e);

// Get CAPS LOCK state.
bool    getcaps();
