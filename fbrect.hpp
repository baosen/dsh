#pragma once
#include "rect.hpp"

// Rectangle image in framebuffer.
class Fbrect : Rect {
    Pos p; // Position.
    Res r; // Resolution.

    friend class Wnd;
public:
    Fbrect();
    Fbrect(const Pos& p, const Res& r);

    // Fill rectangle with colour.
    void   fill(const Col& c) const;

    // Returns the index to its position in the framebuffer.
    uint   i()    const;
    // Returns the rectangle area size.
    size_t size() const;

    // Resize rectangle image.
    void resize(const uint w, const uint h);
};
