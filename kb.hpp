#pragma once
#include <linux/input.h>

// USB keyboard event file.
class kb {
public:
    // Open keyboard event file.
    kb();
    // Close USB keyboard event file.
    ~kb();

    // Open keyboard file.
    void open();
    // Close keyboard file.
    void close();

    // Get keyboard event from event1.
    input_event rd1();
    // Get keyboard event from event2.
    input_event rd2();

    // DEBUG: Used to test reading from keyboard event file.
#ifndef NDEBUG
    void get1();
    void get2();
#endif

private:
   int fdev1, // File descriptor to first keyboard device file representing most of the keys.
       fdev2; // File descriptor to second keyboard device file representing the rest of the keys.
};
