#include "wnd.hpp"
#include "fb.hpp"
using namespace std;

// Create an empty rectangular window in the framebuffer.
wnd::wnd() 
    : pcur(pos(0, 0)), // Set position (0, 0).
      rcur(res(0, 0))  // Set resolution (0, 0).
{}

// Create a rectangular window in the framebuffer.
wnd::wnd(const pos& p, // The position to place the rectangle in the framebuffer.
         const res& r) // The resolution of the rectangle in the framebuffer.
    : pcur(p), rcur(r) 
{}

// Destroy window.
wnd::~wnd()
{
    // TODO: Fill with background color.
}

// Computes the index of its position in the framebuffer.
uint wnd::i() const 
{
    return pcur.i(rcur.w);
}

// Compute start index position.
uint wnd::start(const scr::varinfo& v) const
{
    return pcur.x + pcur.y * v.xres; // The start index of the position.
}

// Get the offsets to the color bits.
prop wnd::cp() const
{
    // Open framebuffer.
    fb         fb;
    const auto v = fb.sc.vinfo();
    prop       p;

    // Set the positions to the color bits.
    p.rlen = v.red.length;
    p.roff = v.red.offset;    // Position to red bits.

    p.glen = v.green.length;
    p.goff = v.green.offset;  // Position to green bits.

    p.blen = v.blue.length;
    p.boff = v.blue.offset;   // Position to blue bits.

    p.alen = v.transp.length;
    p.aoff = v.transp.offset; // Position to alpha-transparency bits.

    return p;
}

#define DOFILL \
    /* Open framebuffer. */ \
    fb fb; \
\
    /* Compute pixel color and position. */ \
    const auto v = fb.sc.vinfo(); \
    const auto s = start(v); /* The start index of the position. */ \
\
    /* Fill the rectangle in Linux framebuffer. */ \
    for (size_t y = 0; y < rcur.h; ++y) \
        for (size_t x = 0; x < rcur.w; ++x) \
            fb.set(s + x + (y * v.xres), c); \

// Fill the rectangular window in the framebuffer with the colour c.
void wnd::fill(const pix& c) // Colour to fill the inside of the rectangle with.
               const 
{
    DOFILL
}

// Fill the rectangular window in the framebuffer with the colour c.
void wnd::fillflip(const pix& c) // Colour to fill the inside of the rectangle with.
                   const 
{
    DOFILL

    // Show it to the user!
    fb.flip();
}

// Get the size/length in bytes of the rectangular window.
size_t wnd::size() const 
{
    return rcur.h * rcur.w;
}

// Returns the window's current position.
pos wnd::p() const
{
    return pcur;
}

// Resize the rectangular window image in the framebuffer.
void wnd::resize(const res& newr) // The new window resolution to resize to.
{
    rcur = newr;
}

// Maximize the rectangular window image to fill the screen.
void wnd::max() 
{
    // Save old positions before maximizing.
    save();

    // Open framebuffer file.
    fb fb;

    // Resize the window to fill the entire screen.
    const auto v = fb.sc.vinfo();
    pcur = pos(0, 0);
    resize(res(v.xres, v.yres));
}

// Save current window graphics.
vector<u32> wnd::savegfx()
{
    vector<u32> tmp(this->size());
    this->read(tmp.data(), 0, this->size());
    return tmp;
}

// Move window to a new position.
void wnd::move(const pos& p)
{
    // Read current window graphic.
    auto tmp = savegfx();

    // TODO: Fill current window with background color.

    // Move window.
    pcur = p;

    // Write back window.
    this->write(tmp.data(), 0, this->size());
}

// Move/set x coordinate position.
void wnd::movex(const uint x)
{
    // Read current window graphic.
    auto tmp = savegfx();

    // TODO: Fill current window with background color.

    // Move window on X axis.
    pcur.x = x;

    // Write back window.
    this->write(tmp.data(), 0, this->size());
}

// Move/set y coordinate position.
void wnd::movey(const uint y)
{
    // Read current window graphic.
    auto tmp = savegfx();

    // TODO: Fill current window with background color.

    // Move window on Y axis.
    pcur.y = y;

    // Write back window.
    this->write(tmp.data(), 0, this->size());
}

// Read from the image buffer of the rectangular window.
int wnd::read(void        *buf,  // Buffer of 32-bit unsigned RGBA pixels.
              const off_t  i,    // offset to write to framebuffer.
              const size_t size) // The size in bytes to write.
              const 
{
    // Check if size of read is out of range.
    if (size > this->size())
        return -EINVAL; // Invalid parameter.

    // Open framebuffer file.
    fb         fb;

    // Get screen attributes.
    const auto v = fb.sc.vinfo(); // Get "variable" screen info.
    const auto s = start(v);      // Compute the start index of the window position.
    const auto w = rcur.w;        // Window width.
    const auto h = rcur.h;        // Window height.

    // Copy row by row to the read buffer.
    // TODO: By bit size.
    for (uint y = 0; y < h; ++y)
        memcpy(rcast<u32*>(buf) + (y * w), 
               &fb.get32(s + i + (y * v.xres)), 
               rcur.w * sizeof(u32));

    return 0; // Operation succeeded.
}

// Write to the picture buffer to the rectangle. Returns exactly the number of bytes written except on error.
int wnd::write(const void  *buf,  // Buffer of 32-bit unsigned RGBA pixels.
               const off_t  i,    // Offset to write to framebuffer.
               const size_t size) // The size in bytes to write.
{
    UNUSED(size);

    // Check if size of the image to be written is larger than the image itself.
    //if (size > this->size())
        //return -EINVAL; // Invalid parameter.

    // Open framebuffer file.
    fb fb;

    // Get screen attributes.
    const auto v = fb.sc.vinfo(); // Get "variable" screen info.
    const auto s = start(v);      // Compute the start index of the window position.
    const auto w = rcur.w;        // Window width.
    const auto h = rcur.h;        // Window height.

    // Copy row by row from the buffer into the framebuffer.
    // TODO: By bit size.
    for (uint y = 0; y < h; ++y)
        memcpy(&fb.get32(s + i + (y * v.xres)), 
               rcast<const u32*>(buf) + (y * w), 
               rcur.w * sizeof(u32));

    // Show it to the user!
    fb.flip();

    // Indicate success!
    return 0; // Operation succeeded.
}

// Save old pos and res of old window.
void wnd::save() 
{
    // Save current rectangle.
    rold = rcur;
    pold = pcur;
}
