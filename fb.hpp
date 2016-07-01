#pragma once
#include <linux/fb.h>
#include "types.hpp"
#include "pos.hpp"
#include "rect.hpp"
#include "col.hpp"

enum Fberr {
    Out_of_range,
};

class Fb {
public:
    Fb();
    uint maxw();
    uint maxh();
    void fill(const Rect& r, const Col& c);
    void fill(const Col& c);
    char& operator()(const Pos&);
    ~Fb();
private:
    void openfb();
    void setup();
    char* map();
    fb_var_screeninfo vinfo();
    fb_fix_screeninfo finfo();

    int fd;
    uint w, h, bpp, 
         roff, goff, boff, aoff,
         rl, gl, bl, al;
    char* fb;
    size_t size;
};
