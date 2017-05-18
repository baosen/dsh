#pragma once
#include "rect.hpp"
#include "pos.hpp"
#include "res.hpp"
#include "col.hpp"

// Rectangle image in framebuffer.
class Fbrect : public Rect {
public:
    Fbrect();
    Fbrect(const Pos& p, const Res& r);

    // Fill rectangle with colour.
    virtual void   fill(const Col& c) const;

    // Returns the index to its position in the framebuffer.
    virtual uint   i()    const;
    // Returns the rectangle area size.
    virtual size_t size() const;

    // Resize rectangle image.
    virtual void resize(const uint w, const uint h);
private:
    Pos p; // Position.
    Res r; // Resolution.

    friend class Wnd;
};
