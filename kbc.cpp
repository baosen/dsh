#include <cwctype>
#include "kbc.hpp"

// US keyboard map.
#define USKBMAP(type, name, size) \
    type name[size] { \
        '\0', /* 0x0000 */ \
        '\0', /* 0x0001 */ \
        '1',  /* 0x0002 */ \
        '2',  /* 0x0003 */ \
        '3',  /* 0x0004 */ \
        '4',  /* 0x0005 */ \
        '5',  /* 0x0006 */ \
        '6',  /* 0x0007 */ \
        '7',  /* 0x0008 */ \
        '8',  /* 0x0009 */ \
        '9',  /* 0x000A */ \
        '0',  /* 0x000B */ \
        '-',  /* 0x000C */ \
        '+',  /* 0x000D */ \
        '\0', /* 0x000E */ \
        '\0', /* 0x000F */ \
        'q',  /* 0x0010 */ \
        'w',  /* 0x0011 */ \
        'e',  /* 0x0012 */ \
        'r',  /* 0x0013 */ \
        't',  /* 0x0014 */ \
        'y',  /* 0x0015 */ \
        'u',  /* 0x0016 */ \
        'i',  /* 0x0017 */ \
        'o',  /* 0x0018 */ \
        'p',  /* 0x0019 */ \
        '{',  /* 0x001A */ \
        '}',  /* 0x001B */ \
        '\n', /* 0x001C */ \
        '\0', /* 0x001D */ \
        'a',  /* 0x001E */ \
        's',  /* 0x001F */ \
        'd',  /* 0x0020 */ \
        'f',  /* 0x0021 */ \
        'g',  /* 0x0022 */ \
        'h',  /* 0x0023 */ \
        'j',  /* 0x0024 */ \
        'k',  /* 0x0025 */ \
        'l',  /* 0x0026 */ \
        ';',  /* 0x0027 */ \
        '\'', /* 0x0028 */ \
    };

// Norwegian keyboard map.
#define NOKBMAP(type, name, size) \
    type name[size] { \
        '\0', /* 0x0000 */ \
        '\0', /* 0x0001 */ \
        '1',  /* 0x0002 */ \
        '2',  /* 0x0003 */ \
        '3',  /* 0x0004 */ \
        '4',  /* 0x0005 */ \
        '5',  /* 0x0006 */ \
        '6',  /* 0x0007 */ \
        '7',  /* 0x0008 */ \
        '8',  /* 0x0009 */ \
        '9',  /* 0x000A */ \
        '0',  /* 0x000B */ \
        '+',  /* 0x000C */ \
        '\\', /* 0x000D */ \
        '\0', /* 0x000E */ \
        '\0', /* 0x000F */ \
        'q',  /* 0x0010 */ \
        'w',  /* 0x0011 */ \
        'e',  /* 0x0012 */ \
        'r',  /* 0x0013 */ \
        't',  /* 0x0014 */ \
        'y',  /* 0x0015 */ \
        'u',  /* 0x0016 */ \
        'i',  /* 0x0017 */ \
        'o',  /* 0x0018 */ \
        'p',  /* 0x0019 */ \
        'å',  /* 0x001A */ \
        '}',  /* 0x001B */ \
        '\n', /* 0x001C */ \
        '\0', /* 0x001D */ \
        'a',  /* 0x001E */ \
        's',  /* 0x001F */ \
        'd',  /* 0x0020 */ \
        'f',  /* 0x0021 */ \
        'g',  /* 0x0022 */ \
        'h',  /* 0x0023 */ \
        'j',  /* 0x0024 */ \
        'k',  /* 0x0025 */ \
        'l',  /* 0x0026 */ \
        'ø',  /* 0x0027 */ \
        'æ',  /* 0x0028 */ \
    };

namespace {
    // Maximum number of keyboard codes.
    const int NCODES = 255;

    // A conversion lookup-table converting a USB keyboard code to an ASCII character.
    USKBMAP(const char, kbascii, NCODES)
    // A conversion lookup-table converting a USB keyboard code to a wide character.
    NOKBMAP(const wchar_t, kbwide, NCODES)

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

// Handle released key event.
static auto released(const __u16 code)
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

// Handle pressed key event.
#define PRESSED(type, name, r1, r2) \
static type name(const __u16 code) \
{ \
    switch (code) { \
    case KEY_LEFTSHIFT: case KEY_RIGHTSHIFT: \
        shift = true; \
        break; \
    case KEY_CAPSLOCK: \
        caps = !caps; \
        break; \
    default: \
        break; \
    } \
\
    if (shift || caps) \
        return r1; \
    return r2; \
}

PRESSED(char, cpressed, toupper(kbascii[code]), kbascii[code])
PRESSED(wchar_t, wcpressed, towupper(kbwide[code]), kbwide[code])

// Handle repeated key event.
#define REPEATED(type, name, r1, r2) \
static type name(const __u16 code) \
{ \
    switch (code) { \
    case KEY_LEFTSHIFT: case KEY_RIGHTSHIFT: \
        shift = true; \
        break; \
    default: \
        break; \
    } \
\
    if (shift || caps) \
        return r1; \
    return r2; \
}

REPEATED(char,     crepeated, toupper(kbascii[code]), kbascii[code])
REPEATED(wchar_t, wcrepeated, towupper(kbwide[code]), kbwide[code])

// Keyboard state.
enum Kbstate {
    RELEASED, // Button is released.
    PRESSED,  // Button is pressed.
    REPEATED  // Button is held, and then gets reported repeately.
};

// Convert keyboard input event to ASCII character.
char toc(const input_event& e) 
{
    // Is it a key event?
    if (e.type != EV_KEY)
        return '\0';

    // Handle key event.
    switch (e.value) {
    case RELEASED:
        return released(e.code);
    case PRESSED:
        return cpressed(e.code);
    case REPEATED:
        return crepeated(e.code);
    default:
        break;
    }

    return '\0';
}

// Convert keyboard input event to Wide character.
wchar_t towc(const input_event& e)
{
    // Is it a key event?
    if (e.type != EV_KEY)
        return '\0';

    // Handle key event.
    switch (e.value) {
    case RELEASED:
        return released(e.code);
    case PRESSED:
        return wcpressed(e.code);
    case REPEATED:
        return wcrepeated(e.code);
    default:
        break;
    }

    return '\0';
}
