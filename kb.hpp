#pragma once
#include <linux/input.h>

class Kb {
public:
    Kb();
    ~Kb();
    int getkbcode();
private:
    input_event read();
};
