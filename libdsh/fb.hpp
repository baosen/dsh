#pragma once
#include "pos.hpp"
#include "rect.hpp"
#include "col.hpp"
#include "scr.hpp"
#include "ptr.hpp"

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
