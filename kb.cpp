#include <cwctype>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstring>
#include <cstdio>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include "types.hpp"
#include "kb.hpp"
using namespace std;

namespace {
    const int  NCODES = 255;

    const char *fpath = "/dev/input/event0";
    int kfd;

    const char *const state[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
    };

    const char kbascii[NCODES] {
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

    bool caps = false;
}

// Opens the keyboard file descriptor.
Kb::Kb() {
    kfd = ::open(fpath, O_RDONLY);

    if (kfd == -1) {
        cerr << "Cannot open " << fpath << ": " << strerror(errno) << endl;
        exit(1);
    }
}

// Reads the keyboard event that is returned by the operating system when the user interacts with the keyboard.
input_event Kb::read()
{
    input_event e;

    // Read e from the keyboard file device.
    forever {
        const ssize_t n = ::read(kfd, &e, sizeof e);

        if (n == (ssize_t)(-1) && errno == EINTR)
            break;
        else if (e.type == EV_KEY) {
            errno = EIO;
            break;
        }
    }

    return e;
}

// Get the pressed keyboard codes from the keyboard queue.
int Kb::getkbcode()
{
    // Reads the keyboard event from the keyboard.
    const auto e = read();

    // Print keyboard code if e is a key change.
    if (e.type == EV_KEY && 0 <= e.value && e.value <= 2)
        printf("%s 0x%04x (%d)\n", state[e.value], (int)(e.code), (int)(e.code));

    // Returns the keyboard code read.
    return e.code;
}

// Returns the ASCII character pressed from the keyboard.
//char readc()
//{
//    const auto code = getkbcode();
//
//    // TODO: Implementing converting characters.
//    throw err("Not implemented yet...");
//
//    return kbascii[code];
//}
//
//// Returns UTF-16 character the user pressed.
//wchar_t readwc()
//{
//    // Get the keyboard code pressed or released.
//    const auto code = getkbcode();
//
//    // Convert the keyboard-code to the corresponding wide character.
//    if (code == KEY_LEFTSHIFT || code == KEY_RIGHTSHIFT) {
//        // Convert to uppercase if the user is holding shift.
//        return towupper(kbwide[code]);
//    } else if (code == KEY_CAPSLOCK) { // To uppercase if user is caps lock is on.
//        // Turn on and off caps lock.
//        caps = !caps;
//    }
//
//    // Convert the keyboard code to the related wide character and return it.
//    return kbwide[code];
//}
