#pragma once
#include <linux/input.h>
class Mouse {
public:
    Mouse();
    ~Mouse();
    input_event read();
};
