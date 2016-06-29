#pragma once
#include <linux/fb.h>
#include "types.hpp"
#include "pos.hpp"
#include "rect.hpp"

class Fb {
public:
    Fb();
    uint maxw();
    uint maxh();
    void fill(const Rect& r, const int c);
    void fill(const int c);
    char& operator()(const Pos&);
    ~Fb();
private:
    void openfb();
    void setup();
    char* map();
    fb_var_screeninfo vinfo();
    fb_fix_screeninfo finfo();

    int fd;
    uint w, h;
    char*  fb;
    size_t size;
};
