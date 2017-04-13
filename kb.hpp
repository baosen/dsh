#pragma once
#include <linux/input.h>

// USB keyboard.
class Kb {
public:
    Kb();
    ~Kb();
    int get();
private:
   input_event rd();
   int fd;
};
