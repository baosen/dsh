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
    uint w, h, bpp, roff, goff, boff, aoff, rl, gl, bl, al;
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

class Ptr {
    size_t size;
    char* fb;
public:
    Ptr() {
    }

    Ptr(Scr& s) {
        size = s.finfo().smem_len;
        fb = scast<char*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, s.fd, 0));
    }

    char& operator[](const uint i) {
        return rcast<char*>(fb)[i];
    }

    Ptr(const Ptr&) {
    }

    Ptr(const Ptr&&) {
    }

    Ptr operator=(const Ptr& p) {
    }

    ~Ptr() {
        if (munmap(fb, size) == -1) {
            perror("Error");
            exit(errno);
        }
    }
};

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
