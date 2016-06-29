#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <linux/input.h>
#include "types.hpp"
#include "kb.hpp"
using namespace std;

namespace {
    // Maximum number of keyboard codes.
    const int NCODES = 255;
    const char *path = "/dev/input/event0";
    const char *const state[3] = {
        "RELEASED",
        "PRESSED ",
        "REPEATED"
    };

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

    bool caps = false; // Caps Lock on?
}

// Opens the keyboard file descriptor.
Kb::Kb() {
    fd = ::open(path, O_RDONLY);
    
    if (fd == -1) {
        cerr << "Cannot open " << path << ": " << strerror(errno) << endl;
        exit(1);
    }
}

Kb::~Kb() {
    if (::close(fd) == -1) {
        cerr << "Cannot close " << path << ": " << strerror(errno) << endl;
        exit(1);
    }
}

// Reads the keyboard event that is returned by the operating system when the user interacts with the keyboard.
input_event Kb::read() {
    input_event e;
    forever {
        const ssize_t n = ::read(fd, &e, sizeof e);
        // Check if it is a keyboard interrupt.
        if (n == (ssize_t)(-1) && errno == EINTR)
            break;
        // Check if it is a key event, which should not happen at all.
        else if (e.type == EV_KEY) {
            errno = EIO;
            break;
        }
    }
    return e;
}

// Get the pressed keyboard codes from the keyboard queue.
int Kb::getkbcode() {
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
