#include <cstring>
#include <sstream>
#include "fio.hpp"
#include "types.hpp"
#include "dbg.hpp"
#include "kb.hpp"
using namespace std;

static const char *path = "/dev/input/event1";

// Creates an empty keyboard.
Kb::Kb() 
    : fd(-2) {}

// Close the keyboard file descriptor.
Kb::~Kb() {
    close();
}

// Open keyboard from file path.
void Kb::open() {
    fd = ::open(path, O_RDONLY);
    if (fd < 0) {
        stringstream ss;
        ss << "Cannot open " << path << ": " << strerror(errno) << endl;
        throw err(ss.str());
    }
    // TODO: Check if it is a keyboard.
}

// Close keyboard event file.
void Kb::close() {
    if (fd == -2)
        return;
    if (::close(fd) < 0) {
        stringstream ss;
        ss << "Cannot close " << path << ": " << strerror(errno) << endl;
        exit(errno); // TODO! What to do when you fail to handle destructor?
    }
}

// Reads the keyboard event that is returned by the operating system when the user interacts with the keyboard.
input_event Kb::rd() {
    input_event e;
    if (::read(fd, &e, sizeof e) < 0) {
        stringstream ss;
        ss << "Failed to read keyboard: " << strerror(errno) << endl;
        throw err(ss.str());
    }
    return e;
}

// Get the pressed keyboard codes from the keyboard queue.
Kb::Kbc Kb::get() {
#ifndef NDEBUG
    // Button state.
    static const char *const state[3] = {
        "Released:",
        "Pressed:",
        "Repeated:"
    };
#endif
    // Reads the keyboard event from the keyboard.
    input_event e;
    do {
        // Read an keyboard event.
        e = rd();
        // Check if key change. If not, continue reading for a key change.
    } while (e.type != EV_KEY || e.value < 0 || e.value > 2);
    // Print keyboard code if e is a key change.
    DBG("%s 0x%04x (%d)\n", state[e.value], (int)(e.code), (int)(e.code));
    // Returns the USB keyboard code read.
    return e.code;
}
