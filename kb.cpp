#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

namespace {
    const char *d = "/dev/input/event1";
    int fd = 0;

    static const char *const evval[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
    };
}

namespace dshell {
    void openkb() {
        fd = open(d, O_RDONLY);
        if (fd == -1) {
            fprintf(stderr, "Cannot open %s: %s.\n", d, strerror(errno));
            exit(1);
        }
    }

    // Get UTF-16 character.
    wchar_t getc() {
        return '\0';
    }
    
    // Get the pressed keyboard codes from the keyboard queue.
    int getkbcode() {
        struct input_event e;
        const ssize_t n = read(fd, &e, sizeof e);

        for (;;) {
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
        if (e.type == EV_KEY && e.value >= 0 && e.value <= 2)
            printf("%s 0x%04x (%d)\n", evval[e.value], (int)e.code, (int)e.code);

        return 0;
    }
}
