#include <cwctype>
#include <linux/input.h>
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
    bool caps = false; 
}

// Convert keyboard code to ASCII.
int toc(const int c) {
    return kbascii[c];
}

// Convert keyboard code to UTF-16 (Wide character).
int towc(const uint c) {
    // Convert the keyboard-code to the corresponding wide character.
    if (c == KEY_LEFTSHIFT || c == KEY_RIGHTSHIFT) {
        // Convert to uppercase if the user is holding shift.
        return towupper(kbwide[c]);
    } else if (c == KEY_CAPSLOCK) { // To uppercase if user is caps lock is on.
        // Turn on and off caps lock.
        caps = !caps;
    }
    // Convert the keyboard code to the related UTF-16 character and return it.
    return kbwide[c];
}
