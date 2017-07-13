#include <cwctype>
#include "kbc.hpp"

// US keyboard map.
#define USKBMAP(type, name) \
    type name[] { \
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

// A conversion lookup-table converting a USB keyboard code to an ASCII character.
static USKBMAP(const char, kbascii)
// A conversion lookup-table converting a USB keyboard code to a wide character.
static USKBMAP(const wchar_t, uskbwide)

// Norwegian keyboard map.
static const wchar_t nokbwide[] {
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
    '|',   /* 0x0029 */
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

// Norwegian keyboard map for UTF-8.
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
    // Is Caps Lock on?
    bool caps  = false; 
    // Is shift held?
    bool shift = false;

    // Current keyboard mapping for wide characters used for laying out the keyboard keys.
    const wchar_t *curmap = nokbwide;
}

// Set keyboard layout.
void setlayout(Layout l)
{
    switch (l) {
    case Layout::US:
        curmap = uskbwide;
        break;
    case Layout::NOR:
        curmap = nokbwide;
        break;
    default:
        break;
    }
}

// Get caps lock state.
bool getcaps()
{
    return caps;
}

// Handle modifiers-keys.
#define MOD \
    if (c == KEY_LEFTSHIFT || c == KEY_RIGHTSHIFT) { \
        shift = true; \
        return '\0'; \
    } else if (c == KEY_CAPSLOCK) { \
        /* Turn on and off caps lock. */ \
        caps = !caps; \
        return '\0'; \
    }

// Convert keyboard code to ASCII.
char toc(const __u16 c) 
{
    // Handle modifiers-keys.
    MOD

    if (c >= ARRAY_SIZE(kbascii))
        return '\0';
    if (shift || caps)
        return toupper(curmap[c]);
    return kbascii[c];
}

// Convert keyboard code to UTF-16 (Wide character).
wchar_t towc(const uint c) 
{
    // Handle modifiers-keys.
    MOD

    // TODO: Array size check.

    // Convert to uppercase if the user is holding shift or caps is on.
    if (shift || caps)
        return towupper(curmap[c]);

    // Convert the keyboard code to the related UTF-16 character and return it.
    return curmap[c];
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
        return '\0'; \
    case KEY_CAPSLOCK: \
        caps = !caps; \
        return '\0'; \
    default: \
        break; \
    } \
\
    if (shift || caps) \
        return r1; \
    return r2; \
}

PRESSED(char,    cpressed,  toupper(kbascii[code]), kbascii[code])
PRESSED(wchar_t, wcpressed, towupper(curmap[code]), curmap[code])

// Handle repeated key event.
#define REPEATED(type, name, r1, r2) \
static type name(const __u16 code) \
{ \
    switch (code) { \
    case KEY_LEFTSHIFT: case KEY_RIGHTSHIFT: \
        shift = true; \
        return '\0'; \
    default: \
        break; \
    } \
\
    if (shift || caps) \
        return r1; \
    return r2; \
}

REPEATED(char,     crepeated, toupper(kbascii[code]), kbascii[code])
REPEATED(wchar_t, wcrepeated, towupper(curmap[code]), curmap[code])

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
