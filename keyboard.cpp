#include <cwctype>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <cstring>
#include <cstdio>
#include "keyboard.hpp"

namespace {
    const char *keyboard_device_file_path = "/dev/input/event1";
    int keyboard_file_descriptor = 0;

    const char *const button_state[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
    };

    // A conversion lookup-table converting a USB keyboard code to a wide character.
    const wchar_t keyboard_to_widechar[MAX_KEYBOARD_CODES] {
        0, 0, 
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
        0,
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n',
        0, // left ctrl.
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 
    };

    bool caps_lock = false;
}

const int READING_ERROR = -1;
const int OPENING_ERROR = -1;

// Opens the keyboard file descriptor.
void open_keyboard()
{
    keyboard_file_descriptor = open(keyboard_device_file_path, O_RDONLY);

    if (keyboard_file_descriptor == OPENING_ERROR) {
        fprintf(stderr, "Cannot open %s: %s.\n", keyboard_device_file_path, strerror(errno));
        exit(EXIT_SUCCESS);
    }
}

#define forever for (;;)

input_event get_keyboard_event()
{
    input_event keyboard_event;

    // Read keyboard_event from the keyboard file device.
    forever {
        const ssize_t bytes_read = read(keyboard_file_descriptor, &keyboard_event, sizeof keyboard_event);
        if (bytes_read == static_cast<ssize_t>(READING_ERROR)) {
            if (errno == EINTR) // Error Interrupt.
                continue;
            else
                break;
        } else {
            if (keyboard_event.type == EV_KEY) {
                errno = EIO; // Error I/O.
                break;
            }
        }
    }

    return keyboard_event;
}

// Get the pressed keyboard codes from the keyboard queue.
int get_keyboard_code()
{
    const auto keyboard_event = get_keyboard_event();

    // Print keyboard code if keyboard_event is a key change.
    if (keyboard_event.type == EV_KEY && 0 <= keyboard_event.value && keyboard_event.value <= 2)
        printf("%s 0x%04x (%d)\n", button_state[keyboard_event.value], (int)keyboard_event.code, (int)keyboard_event.code);

    return keyboard_event.code;
}

// Get UTF-16 character the user pressed.
wchar_t get_wide_character()
{
    // Get the keyboard code pressed or released.
    auto keyboard_code = get_keyboard_code();

    // Convert the keyboard-code to the corresponding wide character.
    if (keyboard_code == KEY_LEFTSHIFT || keyboard_code == KEY_RIGHTSHIFT) // To uppercase if user is holding shift.
        return towupper(keyboard_to_widechar[keyboard_code]);
    else if (keyboard_code == KEY_CAPSLOCK) // To uppercase if user is caps lock is on.
        caps_lock = !caps_lock;

    // Convert the keyboard code to the related wide character and return it.
    return keyboard_to_widechar[keyboard_code];
}