#pragma once
#include "rect.hpp"
#include "pos.hpp"
#include "res.hpp"
#include "col.hpp"
#include "scr.hpp"

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

    // Read from the picture buffer of the rectangle.
    int    read(char *buf, off_t offset, size_t size) const  noexcept;
    // Write to the picture buffer to the rectangle. Returns exactly the number of bytes written except on error.
    int    write(const char *buf, off_t offset, size_t size) noexcept;

private:
    Pos p; // Position of the rectangle in the framebuffer.
    Res r; // Resolution/size of the rectangle in the framebuffer.

    // Compute start index position.
    uint start(const Scr::varinfo& v) const;

    friend class Wnd;
};
