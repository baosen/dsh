#pragma once
#include <linux/input.h>
#include "types.hpp"
//#include "utf8.hpp"

// Convert keyboard code to an ASCII character.
char     toc(const  __u16 c);
// Convert keyboard input event to an ASCII character.
char     toc(const input_event& e);

// Convert keyboard code to an Wide character.
wchar_t  towc(const uint c);
// Convert keyboard input event to an Wide character.
wchar_t  towc(const input_event& e);

// Convert keyboard input event to an UTF-8 character.
//UTF8char tou8(const input_event& e);

// Get CAPS LOCK state.
bool     getcaps();
