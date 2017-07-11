#include <cwctype>
#include "kbc.hpp"

namespace {
    // Maximum number of keyboard codes.
    const int NCODES = 255;

    // A conversion lookup-table converting a USB keyboard code to an ASCII character.
    const char kbascii[NCODES] {
        0, 0, 
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
        0,
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n',
        0, // left ctrl.
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 
    };
    // A conversion lookup-table converting a USB keyboard code to a wide character.
    const wchar_t kbwide[NCODES] {
        0, 0, 
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
        0,
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n',
        0, // left ctrl.
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 
    };

    // Is Caps Lock on?
    bool caps  = false; 
    // Is shift held?
    bool shift = false;
}

// Convert keyboard code to ASCII.
char toc(const __u16 c) 
{
    return kbascii[c];
}

// Get caps lock state.
bool getcaps()
{
    return caps;
}

// Convert keyboard code to UTF-16 (Wide character).
wchar_t towc(const uint c) 
{
    // Convert the keyboard-code to the corresponding wide character.
    if (c == KEY_LEFTSHIFT || c == KEY_RIGHTSHIFT) {
        // Convert to uppercase if the user is holding shift.
        shift = true;
    } else if (c == KEY_CAPSLOCK) { // To uppercase if user is caps lock is on.
        // Turn on and off caps lock.
        caps = !caps;
    }

    // Convert the keyboard code to the related UTF-16 character and return it.
    if (shift || caps)
        return towupper(kbwide[c]);
    return kbwide[c];
}

static wchar_t released(const __u16 code)
{
    switch (code) {
    case KEY_LEFTSHIFT: case KEY_RIGHTSHIFT:
        shift = false;
        break; 
    default:
        break;
    }

    return '\0';
}

static wchar_t pressed(const __u16 code)
{
    switch (code) {
    case KEY_LEFTSHIFT: case KEY_RIGHTSHIFT:
        shift = true;
        break;
    case KEY_CAPSLOCK:
        caps = !caps;
        break;
    default:
        break;
    }

    if (shift || caps)
        return towupper(kbwide[code]);
    return kbwide[code];
}

static wchar_t repeated(const __u16 code)
{
    switch (code) {
    case KEY_LEFTSHIFT: case KEY_RIGHTSHIFT:
        shift = true;
        break;
    default:
        break;
    }
    
    if (shift || caps)
        return towupper(kbwide[code]);
    return kbwide[code];
}

wchar_t towc(const input_event& e)
{
    // Keyboard state.
    enum Kbstate {
        RELEASED, // Button is released.
        PRESSED,  // Button is pressed.
        REPEATED  // Button is held, and then gets reported repeately.
    };

    // Is it a key event?
    if (e.type != EV_KEY)
        return '\0';

    // Handle key event.
    switch (e.value) {
    case RELEASED:
        return released(e.code);
    case PRESSED:
        return pressed(e.code);
    case REPEATED:
        return repeated(e.code);
    default:
        break;
    }

    return '\0';
}
