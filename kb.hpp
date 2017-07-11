#pragma once
#include <linux/input.h>

// USB keyboard event file.
class Kb {
public:
    // Open keyboard event file.
    Kb();
    // Close USB keyboard event file.
    ~Kb();

    // Open keyboard file.
    void open();
    // Close keyboard file.
    void close();

    // Get keyboard code pressed.
    int get();
    // Get input event from keyboard.
    input_event rd();
private:

   int fd; // File descriptor to keyboard device file.
};
