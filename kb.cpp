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
    const char *d = "/dev/input/event1";
    int fd = 0;

    const char *const state[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
    };

    const wchar_t kbcode2wchar[MAX_KEYBOARD_CODES] {
        0, 0, 
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
        0,
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n',
        0, // left ctrl.
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 
    };

    bool caps = false;
}

void open_keyboard() {
    fd = open(d, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", d, strerror(errno));
        exit(1);
    }
}

// Get the pressed keyboard codes from the keyboard queue.
int get_keyboard_code() {
    struct input_event event;

    for (;;) {
        const ssize_t n = read(fd, &event, sizeof event);
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
            if (event.type == EV_KEY) {
                errno = EIO;
                break;
            }
    }
    if (event.type == EV_KEY && 0 <= event.value && event.value <= 2)
        printf("%s 0x%04x (%d)\n", state[event.value], (int)event.code, (int)event.code);

    return event.code;
}

// Get UTF-16 character.
wchar_t get_wide_character() {
    auto kbcode = get_keyboard_code();
    if (kbcode == KEY_LEFTSHIFT || kbcode == KEY_RIGHTSHIFT)
        return towupper(kbcode2wchar[kbcode]);
    else if (kbcode == KEY_CAPSLOCK)
        caps = !caps;
    return kbcode2wchar[kbcode];
}
