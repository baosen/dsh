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

    // Move window to new position.
    void   move(const Pos& p);
    // Resize window.
    void   resize(const Res&);
    // Maximize the window to fill the entire screen.
    void   max();
    // Minimize the window.
    void   min();

    // Read from the picture buffer of the rectangular window.
    int    read(char *buf, off_t offset, size_t size) const  noexcept;
    // Write to the picture buffer of the rectangular window. Returns exactly the number of bytes written except on error.
    int    write(const char *buf, off_t offset, size_t size) noexcept;
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
