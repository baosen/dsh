#pragma once
#include "rect.hpp"
#include "pos.hpp"
#include "res.hpp"
#include "col.hpp"

// Rectangle image in framebuffer.
class Rect {
public:
    Rect();
    Rect(const Pos& p, const Res& r);

    // Fill rectangle with colour.
    void   fill(const Col& c) const;

    // Returns the index to its position in the framebuffer.
    uint   i()    const;
    // Returns the rectangle area size.
    size_t size() const;

    // Resize rectangle image.
    void   resize(const uint w, const uint h);

    // Maximize the rectangle to fill the screen.
    void   max();
private:
    Pos p; // Position.
    Res r; // Resolution.

    friend class Wnd;
};
