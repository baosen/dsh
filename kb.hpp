#pragma once
#include <linux/input.h>

// USB keyboard event file.
class Kb {
public:
    // Keyboard code.
    typedef int Kbc;

    // Open keyboard event file.
    Kb();
    // Close USB keyboard event file.
    ~Kb();

    // Open keyboard file.
    void open();
    // Close keyboard file.
    void close();

    // Get keyboard code pressed.
    Kbc get();
private:
   input_event rd();
   int fd;
};
