#pragma once
#include <linux/input.h>

class Mouse {
public:
    Mouse();
    ~Mouse();
    void read();
};
