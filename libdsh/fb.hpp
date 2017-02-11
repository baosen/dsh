#pragma once
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include "types.hpp"
#include "pos.hpp"
#include "rect.hpp"
#include "col.hpp"

class Ptr;

// Computer screen.
class Scr {
    int fd;
    uint w,   // width.
         h,   // height.
         bpp, // bits per pixel.
         roff, goff, boff, aoff, 
         rl, gl, bl, al;
    size_t size;
    char* fb;
    friend class Ptr;
    friend class Fb;
public:
    typedef fb_var_screeninfo varinfo;
    typedef fb_fix_screeninfo fixinfo;

    Scr();
    ~Scr();

    varinfo vinfo();
    fixinfo finfo();

    int ctl(unsigned long, ...);
    Ptr map();
};

#include "scr.hpp"

// Framebuffer.
class Fb {
    Scr  scr;
    Ptr  fb;
    friend class Rect;
public:
    enum Err {
        OOR, // Out of range.
    };
    Fb();
    ~Fb();

    uint maxw();
    uint maxh();

    void fill(const Rect& r, const Col& c);
    void fill(const Col& c);

    char& operator()(const Pos&);
};

class Fill {
    Fb f;
public:
    Fill(const Rect& r, const Col& c) {
        f.fill(r, c);
    }
};
