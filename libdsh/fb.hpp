#pragma once
#include "pos.hpp"
#include "rect.hpp"
#include "col.hpp"
#include "scr.hpp"

// Framebuffer.
class Fb {
    Scr  scr;

    size_t size;
    char*  fb;

    friend class Rect;
public:
    // Grab framebuffer.
    Fb();
    // Release framebuffer.
    ~Fb();

    // Access its memory.
    char& operator[](const uint i);
};

class Fill {
    Fb f;
public:
    Fill(const Rect& r, const Col& c) {
        f.fill(r, c);
    }
};
