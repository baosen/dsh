#include <cstring>
#include <sstream>
#include <iostream>
#include "fio.hpp"
#include "types.hpp"
#include "dbg.hpp"
#include "kb.hpp"
using namespace std;

static const char *pathev1  = "/dev/input/event1";
static const char *pathev2  = "/dev/input/event2";
static const int  NONE      = -2;

// Creates an empty keyboard that is not opened yet.
Kb::Kb()
    : fdev1(NONE), // Set it to not opened.
      fdev2(NONE)  // Set it to not opened.
{}

// Close the keyboard file descriptor.
Kb::~Kb() 
{
    close();
}

// Open keyboard from file path.
void Kb::open() 
{
    // Open first main keyboard device file.
    fdev1 = ::open(pathev1, O_RDONLY); // Blocking. Setting O_NONBLOCK to not block does not seem to work.
    if (fdev1 < 0) {
        stringstream ss;
        ss << "Cannot open " << pathev1 << ": " << strerror(errno) << endl;
        throw err(ss.str());
    }
    // Open second extra keyboard device file.
    fdev2 = ::open(pathev2, O_RDONLY);
    if (fdev2 < 0) {
        fdev1 = NONE;
        stringstream ss;
        ss << "Cannot open " << pathev2 << ": " << strerror(errno) << endl;
        throw err(ss.str());
    }
    // TODO: Check if it is a keyboard.
}

// Close keyboard event file.
void Kb::close() 
{
    if (fdev1 != NONE && ::close(fdev1) < 0) {
        stringstream ss;
        ss << "Cannot close " << pathev1 << ": " << strerror(errno) << endl;
        exit(errno); // TODO! What to do when you fail to handle destructor?
    }
    if (fdev2 != NONE && ::close(fdev2) < 0) {
        stringstream ss;
        ss << "Cannot close " << pathev2 << ": " << strerror(errno) << endl;
        exit(errno); // TODO! What to do when you fail to handle destructor?
    }
}

// DEBUG: Used to test reading from keyboard event file.
#ifndef NDEBUG
// Button state.
static const char *const state[3] = {
    "Released:",
    "Pressed:",
    "Repeated:"
};

#define GET(rd, name) \
void Kb::name() \
{ \
    /* Reads the keyboard event from the keyboard. */ \
    input_event e; \
    do { \
        /* Wait for a keyboard input event and read it. */ \
        e = rd(); \
        /* Check if key change. If not, continue reading for a key change. */ \
    } while (e.type != EV_KEY ||          /* Is it a key event? */ \
             e.value < 0 || e.value > 2); /* Does it contain a valid state? */ \
\
    /* Print keyboard code if e is a key change. */ \
    DBG("%s 0x%04x (%d)\n",  \
        state[e.value],      /* Show current button state. */ \
        scast<int>(e.code),  /* Show its code in 16-bit hex. */ \
        scast<int>(e.code)); /* Show its code as integer value. */ \
\
} \

GET(rd1, get1)
GET(rd2, get2)

#endif

// Get the keyboard event that is returned by the operating system when the user interacts with the keyboard.
#define RD(name, fd) \
input_event Kb::name() \
{ \
    /* Check if keyboard is opened yet. */ \
    if (fd == NONE) \
        throw err("No keyboard device file opened yet!"); \
\
    /* Wait for a keyboard input event and read it. */ \
    input_event e; \
\
    if (::read(fd, &e, sizeof e) < 0) { \
        stringstream ss; \
        ss << "Cannot read keyboard input event: " << strerror(errno) << endl; \
        throw err(ss.str()); \
    } \
\
    return e; \
} \

RD(rd1, fdev1)
RD(rd2, fdev2)
