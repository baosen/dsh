#include <cstdlib>
#include <cwctype>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <cstring>
#include <cstdio>

namespace {
    const char *d = "/dev/input/event1";
    int fd = 0;

    const char *const state[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
    };

    const wchar_t c2wchar[255] {
        0, 0, 
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
        0,
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', '\n',
        0, // left ctrl.
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', 
    };

    bool caps = false;
}

void openkb() {
    fd = open(d, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", d, strerror(errno));
        exit(1);
    }
}

// Get the pressed keyboard codes from the keyboard queue.
int getkbcode() {
    struct input_event e;

    for (;;) {
        const ssize_t n = read(fd, &e, sizeof e);
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
            if (e.type == EV_KEY) {
                errno = EIO;
                break;
            }
    }
    if (e.type == EV_KEY && 0 <= e.value && e.value <= 2)
        printf("%s 0x%04x (%d)\n", state[e.value], (int)e.code, (int)e.code);

    return e.code;
}

// Get UTF-16 character.
wchar_t getc() {
    auto c = getkbcode();
    if (c == KEY_LEFTSHIFT || c == KEY_RIGHTSHIFT)
        return towupper(c2wchar[c]);
    else if (c == KEY_CAPSLOCK)
        caps = !caps;
    return c2wchar[c];
}
