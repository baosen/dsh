#include <cstring>
#include <sstream>
#include "fio.hpp"
#include "types.hpp"
#include "dbg.hpp"
#include "kb.hpp"
using namespace std;

static const char *path = "/dev/input/event1";
static const int  NONE  = -2;

// Creates an empty keyboard.
Kb::Kb() 
    : fd(NONE) {}

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
    if (fd == NONE)
        return;
    if (::close(fd) < 0) {
        stringstream ss;
        ss << "Cannot close " << path << ": " << strerror(errno) << endl;
        exit(errno); // TODO! What to do when you fail to handle destructor?
    }
}

// Get the pressed keyboard codes from the keyboard queue.
int Kb::get() {
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
    } while (e.type != EV_KEY ||          // Is it a key event?
             e.value < 0 || e.value > 2); // Does it contain a valid state?

    // Print keyboard code if e is a key change.
    DBG("%s 0x%04x (%d)\n", 
        state[e.value],      // Show current button state.
        scast<int>(e.code),  // Show its code in 16-bit hex.
        scast<int>(e.code)); // Show its code as integer value.

    // Returns the USB keyboard code read.
    return e.code;
}

// Reads the keyboard event that is returned by the operating system when the user interacts with the keyboard.
input_event Kb::rd() {
    // Check if keyboard is opened yet.
    if (fd == NONE)
        throw err("No keyboard device file opened yet!");

    // Read keyboard input event.
    // TODO: Why can't you read æøå,.?
    input_event e;
    if (::read(fd, &e, sizeof e) < 0) {
        stringstream ss;
        ss << "Cannot read keyboard code: " << strerror(errno) << endl;
        throw err(ss.str());
    }
    return e;
}
