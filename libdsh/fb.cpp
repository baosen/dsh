#include <cstring>
#include "types.hpp"
#include "rect.hpp"
#include "fb.hpp"
#include "col.hpp"

// Setup framebuffer file.
Fb::Fb() {
    fb = scr.map();
}

// Unmap framebuffer from address space.
Fb::~Fb() {
    // TODO:
}

// Assign a pixel to (x, y) in the framebuffer.
char& Fb::operator()(const Pos& p) {
    const auto i = p.i(scr.w);
    if (i >= scr.w * scr.h)
        throw Fb::Err::OOR;
    return fb[i];
}

// Fill a rectangle in the framebuffer with a color.
void Fb::fill(const Rect& r, const Col& c) {
    if (r.i() >= scr.w * scr.h)
        throw Fb::Err::OOR;
    r.fill(fb, c);
}

// Fill the entire screen with a color.
void Fb::fill(const Col& c) {
    const auto p = c.val(scr.roff, scr.goff, scr.boff);
    for (size_t i = 0; i < scr.w*scr.h; ++i)
        fb.i32(i) = p;
}
