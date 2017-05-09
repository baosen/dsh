#pragma once
#include <linux/input.h>

// USB keyboard.
class Kb {
public:
    Kb();
    ~Kb();
    void open();
    int  get();
private:
   input_event rd();
   int fd;
};
