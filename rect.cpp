#include "rect.hpp"
#include "fb.hpp"
using namespace std;

// Create an empty rectangle in the framebuffer.
Rect::Rect() {}

// Create a rectangle in the framebuffer.
Rect::Rect(const Pos& p, // The position to place the rectangle in the framebuffer.
           const Res& r) // The resolution of the rectangle in the framebuffer.
    : p(p), r(r) {}

// Computes the index of its position in the framebuffer.
uint Rect::i() const 
{
    return p.i(r.w);
}

// Fill rectangle in framebuffer with the colour c.
void Rect::fill(const Col& c) // Colour to fill the inside of the rectangle with.
                const 
{
    // Open framebuffer.
    Fb fb;

    // Compute pixel color and position.
    const auto v = fb.scr.vinfo();
    const auto s = p.x + p.y * v.xres; // The start index of the position.

    // Fill the rectangle in Linux framebuffer.
    for (size_t y = 0; y < r.h; ++y)
        for (size_t x = 0; x < r.w; ++x)
            fb.set(s+x+(y*v.xres), c);
}

// Get the size in bytes of the rectangle.
size_t Rect::size() const 
{
    return r.h*r.w;
}

// Resize the rectangle image in the framebuffer.
void Rect::resize(const uint w, const uint h) 
{
    r.w = w;
    r.h = h;
    // TODO: Redraw the rectangle in the framebuffer.
}

// Maximize the rectangle to fill the screen.
void Rect::max() 
{
    // Open framebuffer file.
    Fb         fb;
    // Resize the rectangle to fill the entire screen.
    const auto v = fb.scr.vinfo();
    resize(v.xres, v.yres);
}

// Read from the picture buffer of the rectangle.
int Rect::read(char  *buf,  // Buffer of 32-bit unsigned RGBA pixels.
               off_t  i,    // Offset to write to framebuffer.
               size_t size) // The size in bytes to write.
               const 
               noexcept
{
    // Check if size of read is out of range.
    if (size > this->size())
        return -EINVAL; // Invalid parameter.
    // Open framebuffer file.
    Fb         fb;
    // Get screen attributes.
    const auto v = fb.scr.vinfo();
    const auto s = p.x+p.y*v.xres;
    // TODO: Read framebuffer, convert and copy pixels to the buffer provided by the caller.
    const auto w = this->r.w;
    for (size_t y = 0; y < r.h; ++y) {
        for (size_t x = 0; x < r.w; ++x) {
            u32* p = rcast<u32*>(buf);
        }
    }
    return 0; // Operation succeeded.
}

// Write to the picture buffer to the rectangle. Returns exactly the number of bytes written except on error.
int Rect::write(const char *buf,  // Buffer of 32-bit unsigned RGBA pixels.
                off_t       i,    // Offset to write to framebuffer.
                size_t      size) // The size in bytes to write.
                noexcept
{
    // Check if size of write is out of range.
    if (size > this->size())
        return -EINVAL; // Invalid parameter.
    // Open framebuffer file.
    Fb         fb;
    // Get screen attributes.
    const auto v = fb.scr.vinfo();
    const auto s = p.x+p.y*v.xres; // Compute the start index of the position.
    // Convert pixels in the given buffer and write it to the framebuffer file.
    const auto w = this->r.w;
    for (uint y = 0; y < r.h; ++y) {
        for (uint x = 0; x < r.w; ++x) {
            // Assume 32-bit unsigned RGBA pixels.
            const u32* p = rcast<const u32*>(buf);
            uint       r = p[0+x+y*w], // 32-bit red.
                       g = p[1+x+y+w], // 32-bit green.
                       b = p[2+x+y+w], // 32-bit blue.
                       a = p[3+x+y+w]; // 32-bit alpha-transparency.
            fb.set(s+x+y*v.xres, Col(r, g, b, a));
        }
    }
    return 0; // Operation succeeded.
}
