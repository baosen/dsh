#pragma once
#include "pos.hpp"
#include "res.hpp"
#include "pix.hpp"
#include "scr.hpp"

// Rectangle image in framebuffer.
class Wnd {
public:
    Wnd();
    Wnd(const Pos& p, const Res& r);

    // Fill window with a colour.
    void   fill(const Pix& c) const;

    // Returns the index to its position in the framebuffer.
    uint   i()    const;
    // Returns the window (rectangle) area size.
    size_t size() const;
    // Returns the window's current position.
    Pos    pos() const;

    Off    off() const;

    // Move window to new position.
    void   move(const Pos& p);
    // Resize window.
    void   resize(const Res&);
    // Maximize the window to fill the entire screen.
    void   max();
    // Minimize the window.
    void   min();

    // Read from the image buffer of the rectangular window.
    int    read(void        *buf, // Buffer to read to.
                const off_t  i,   // Offset in elements to read from.
                const size_t n)   // Number of elements to read.
                const
                noexcept;

    // Write to the image buffer of the rectangular window. Returns exactly the number of elements written except on error.
    int    write(const void  *buf, 
                 const off_t  i, 
                 const size_t n) noexcept;
protected:
    // Window position:
    Pos pcur, // Current position of the rectangle in the framebuffer. 
        pold; // Old position before switching.

    // Window resolution:
    Res rcur, // Current resolution/size of the rectangle in the framebuffer.
        rold; // Old resolution before switching.

private:
    // Compute start index position.
    uint start(const Scr::varinfo& v) const;
    // Save old window state.
    void save();
};
