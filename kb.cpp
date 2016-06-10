#include <cstdlib>
#include <cwctype>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <cstring>
#include <cstdio>
#include "kb.hpp"

namespace {
    const char *keyboard_dev_file_path = "/dev/input/event1";
    int keyboard_file_desc = 0;

    const char *const button_state[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
    };

    // A conversion lookup-table converting a USB keyboard code to a wide character.
    const wchar_t kbcode2wchar[MAX_KEYBOARD_CODES] {
        0, 0, 
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
        0,
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n',
        0, // left ctrl.
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 
    };

    bool caps_lock = false;
}

#define ERROR -1

// Opens the keyboard file descriptor.
void open_keyboard() {
    keyboard_file_desc = open(keyboard_dev_file_path, O_RDONLY);

    if (keyboard_file_desc == ERROR) {
        fprintf(stderr, "Cannot open %s: %s.\n", keyboard_dev_file_path, strerror(errno));
        exit(1);
    }
}

// Get the pressed keyboard codes from the keyboard queue.
int get_keyboard_code() {
    struct input_event event;

    // Read event from the keyboard file device.
    for (;;) {
        const ssize_t bytes_read = read(keyboard_file_desc, 
                                        &event, sizeof event);
        if (bytes_read == (ssize_t)ERROR) {
            if (errno == EINTR) // Error Interrupt.
                continue;
            else
                break;
        } else
            if (event.type == EV_KEY) {
                errno = EIO; // Error I/O.
                break;
            }
    }
    // Print keyboard code if event is a key change.
    if (event.type == EV_KEY && 0 <= event.value && event.value <= 2)
        printf("%s 0x%04x (%d)\n", button_state[event.value], 
                                   (int)event.code, (int)event.code);

    return event.code;
}

// Get UTF-16 character the user pressed.
wchar_t get_wide_character() {
    // Get the keyboard code pressed or released.
    auto keyboard_code = get_keyboard_code();

    // Convert the keyboard-code to the corresponding wide character.
    if (keyboard_code == KEY_LEFTSHIFT || keyboard_code == KEY_RIGHTSHIFT) // To uppercase if user is holding shift.
        return towupper(kbcode2wchar[keyboard_code]);
    else if (keyboard_code == KEY_CAPSLOCK) // To uppercase if user is caps lock is on.
        caps_lock = !caps_lock;
    return kbcode2wchar[keyboard_code];
}
