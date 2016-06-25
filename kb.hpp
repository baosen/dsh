#pragma once
#include <linux/input.h>

class Kb {
public:
    Kb();
    int getkbcode();
private:
    input_event read();
};
