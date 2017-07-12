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
const wchar_t kbwide[] {
    '\0',  /* 0x0000 */
    '\0',  /* 0x0001 */
    '1',   /* 0x0002 */
    '2',   /* 0x0003 */
    '3',   /* 0x0004 */
    '4',   /* 0x0005 */
    '5',   /* 0x0006 */
    '6',   /* 0x0007 */
    '7',   /* 0x0008 */
    '8',   /* 0x0009 */
    '9',   /* 0x000A */
    '0',   /* 0x000B */
    '+',   /* 0x000C */
    '\\',  /* 0x000D */
    '\0',  /* 0x000E */
    '\0',  /* 0x000F */
    'q',   /* 0x0010 */
    'w',   /* 0x0011 */
    'e',   /* 0x0012 */
    'r',   /* 0x0013 */
    't',   /* 0x0014 */
    'y',   /* 0x0015 */
    'u',   /* 0x0016 */
    'i',   /* 0x0017 */
    'o',   /* 0x0018 */
    'p',   /* 0x0019 */
   L'å',   /* 0x001A */
   L'¨',   /* 0x001B */
    '\n',  /* 0x001C */
    '\0',  /* 0x001D */
    'a',   /* 0x001E */
    's',   /* 0x001F */
    'd',   /* 0x0020 */
    'f',   /* 0x0021 */
    'g',   /* 0x0022 */
    'h',   /* 0x0023 */
    'j',   /* 0x0024 */
    'k',   /* 0x0025 */
    'l',   /* 0x0026 */
   L'ø',   /* 0x0027 */
   L'æ',   /* 0x0028 */
    'c',   /* 0x0029 */
    'r',   /* 0x002A */
    '\'',  /* 0x002B */
    'z',   /* 0x002C */
    'x',   /* 0x002D */
    'c',   /* 0x002E */
    'v',   /* 0x002F */
    'b',   /* 0x0030 */
    'n',   /* 0x0031 */
    'm',   /* 0x0032 */
    ',',   /* 0x0033 */
    '.',   /* 0x0034 */
    '-',   /* 0x0035 */
    '\0',  /* 0x0036 */
    '\0',  /* 0x0037 */
    '\0',  /* 0x0038 */
    ' ',   /* 0x0039 */
    '\0',  /* 0x003A */
    '\0',  /* 0x003B */
    '\0',  /* 0x003C */
    '\0',  /* 0x003D */
    '\0',  /* 0x003E */
    '\0',  /* 0x003F */
    '\0',  /* 0x0040 */
    '\0',  /* 0x0041 */
    '\0',  /* 0x0042 */
    '\0',  /* 0x0043 */
    '\0',  /* 0x0044 */
    '\0',  /* 0x0045 */
    '\0',  /* 0x0046 */
    '\0',  /* 0x0047 */
    '\0',  /* 0x0048 */
    '\0',  /* 0x0049 */
    '\0',  /* 0x004A */
    '\0',  /* 0x004B */
    '\0',  /* 0x004C */
    '\0',  /* 0x004D */
    '\0',  /* 0x004E */
    '\0',  /* 0x004F */
    '\0',  /* 0x0050 */
    '\0',  /* 0x0051 */
    '\0',  /* 0x0052 */
    '\0',  /* 0x0053 */
    '\0',  /* 0x0054 */
    '\0',  /* 0x0055 */
    '<',   /* 0x0056 */
    '\0',  /* 0x0057 */
    '\0',  /* 0x0058 */
    '\0',  /* 0x0059 */
    '\0',  /* 0x005A */
    '\0',  /* 0x005B */
    '\0',  /* 0x005C */
    '\0',  /* 0x005D */
    '\0',  /* 0x005E */
    '\0',  /* 0x005F */
};

// Norwegian keyboard map.
//UTF8char kbnor[] {
//        '\0',  /* 0x0000 */
//        '\0',  /* 0x0001 */
//        '1',   /* 0x0002 */
//        '2',   /* 0x0003 */
//        '3',   /* 0x0004 */
//        '4',   /* 0x0005 */
//        '5',   /* 0x0006 */
//        '6',   /* 0x0007 */
//        '7',   /* 0x0008 */
//        '8',   /* 0x0009 */
//        '9',   /* 0x000A */
//        '0',   /* 0x000B */
//        '+',   /* 0x000C */
//        '\\',  /* 0x000D */
//        '\0',  /* 0x000E */
//        '\0',  /* 0x000F */
//        'q',   /* 0x0010 */
//        'w',   /* 0x0011 */
//        'e',   /* 0x0012 */
//        'r',   /* 0x0013 */
//        't',   /* 0x0014 */
//        'y',   /* 0x0015 */
//        'u',   /* 0x0016 */
//        'i',   /* 0x0017 */
//        'o',   /* 0x0018 */
//        'p',   /* 0x0019 */
//      u8"å",   /* 0x001A */
//        '}',   /* 0x001B */
//        '\n',  /* 0x001C */
//        '\0',  /* 0x001D */
//        'a',   /* 0x001E */
//        's',   /* 0x001F */
//        'd',   /* 0x0020 */
//        'f',   /* 0x0021 */
//        'g',   /* 0x0022 */
//        'h',   /* 0x0023 */
//        'j',   /* 0x0024 */
//        'k',   /* 0x0025 */
//        'l',   /* 0x0026 */
//      u8"ø",   /* 0x0027 */
//      u8"æ",   /* 0x0028 */
//};

namespace {
    // Maximum number of keyboard codes.
    const int NCODES = 255;

    // A conversion lookup-table converting a USB keyboard code to an ASCII character.
    USKBMAP(const char, kbascii, NCODES)
    // A conversion lookup-table converting a USB keyboard code to a wide character.
    //USKBMAP(const wchar_t, kbwide, NCODES)

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

/*
// Convert keyboard input event to UTF-8 character.
UTF8char tou8(const input_event& e)
{
    // Is it a key event?
    if (e.type != EV_KEY)
        return UTF8char();

    // Handle key event.
    switch (e.value) {
    case RELEASED:
        // TODO!
    case PRESSED:
        // TODO!
    case REPEATED:
        // TODO!
    default:
        break;
    }

    return UTF8char();
}
*/
