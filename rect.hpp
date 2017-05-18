#pragma once
#include "pos.hpp"
#include "res.hpp"
#include "col.hpp"
#include "fb.hpp"

// Rectangle interface.
class Rect {
public:
    // Fill rectangle with colour.
    virtual void   fill(const Col& c) const = 0;

    // Returns the index to its position in the rectangle.
    virtual uint   i()    const = 0;
    // Returns the rectangle area size.
    virtual size_t size() const = 0;

    // Resize rectangle image.
    virtual void resize(const uint w, const uint h) = 0;
};
