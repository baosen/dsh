#pragma once
#include <linux/input.h>
class Ms {
public:
    Ms();
    ~Ms();
    input_event read();
};
