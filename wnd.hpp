#pragma once
#include "pos.hpp"
#include "res.hpp"
#include "pix.hpp"
#include "scr.hpp"

namespace wsys {
    uint getx(const char *name);
    uint gety(const char *name);
}

// Rectangle image in framebuffer.
class wnd {
public:
    // Create a window in the framebuffer.
    wnd();
    // Create a window at position p and resolutionr in the framebuffer.
    wnd(const pos& p, const res& r);
    // Destroy the window.
    ~wnd();

    // Returns the index to its position in the framebuffer.
    uint   i()    const;
    // Returns the window (rectangle) area size.
    size_t size() const;
    // Returns the window's current position.
    pos    p()    const;
    // Returns the window's color properties.
    prop   cp()   const;


    // Move window to a new position.
    void   move(const pos& p);
    // Move/set x coordinate position.
    void   movex(const uint x);
    // Move/set y coordinate position.
    void   movey(const uint y);

    // Resize window.
    void   resize(const res& newres);
    // Maximize the window to fill the entire screen.
    void   max();
    // Minimize the window.
    void   min();

    // Fill window with a colour.
    void   fill(const pix& c) // Color the fill with.
                const;
    // Fill window with a colour and flip.
    void   fillflip(const pix& c) // Color to fill with.
                    const;
    // Read from the image buffer of the rectangular window.
    int    read(void        *buf, // Buffer to read to.
                const off_t  i,   // Offset in elements to read from.
                const size_t n)   // Number of elements to read.
                const;
    // Write to the image buffer of the rectangular window. Returns exactly the number of elements written except on error.
    int    write(const void  *buf, 
                 const off_t  i, 
                 const size_t n);
protected:
    // Window position:
    pos pcur, // Current position of the rectangle in the framebuffer. 
        pold; // Old position before switching.

    // Window resolution:
    res rcur, // Current resolution/size of the rectangle in the framebuffer.
        rold; // Old resolution before switching.

private:
    // Compute start index position.
    uint start(const scr::varinfo& v) const;

    // Save old window state.
    void save();

    friend uint wsys::getx(const char *name);
    friend uint wsys::gety(const char *name);
};
