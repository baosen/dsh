#include "wnd.hpp"
#include "fb.hpp"
using namespace std;

// Create an empty rectangular window in the framebuffer.
wnd::wnd() {}

// Create a rectangular window in the framebuffer.
wnd::wnd(const pos& p, // The position to place the rectangle in the framebuffer.
         const res& r) // The resolution of the rectangle in the framebuffer.
    : pcur(p), rcur(r) {}

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

off wnd::o() const
{
    // Set the positions to the color bits.
    fb         fb;
    const auto v = fb.sc.vinfo();
    off        o;

    if (v.red.length)
        o.roff = v.red.offset;    // Position to red bits.
    if (v.green.length)
        o.goff = v.green.offset;  // Position to green bits.
    if (v.blue.length)
        o.boff = v.blue.offset;   // Position to blue bits.
    if (v.transp.length)
        o.aoff = v.transp.offset; // Position to alpha-transparency bits.
    return o;
}

// Fill the rectangular window in the framebuffer with the colour c.
void wnd::fill(const pix& c) // Colour to fill the inside of the rectangle with.
               const 
{
    // Open framebuffer.
    fb fb;

    // Compute pixel color and position.
    const auto v = fb.sc.vinfo();
    const auto s = start(v); // The start index of the position.

    // Fill the rectangle in Linux framebuffer.
    for (size_t y = 0; y < rcur.h; ++y)
        for (size_t x = 0; x < rcur.w; ++x)
            fb.set(s + x + (y * v.xres), c);

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

// Read from the image buffer of the rectangular window.
int wnd::read(void        *buf,  // Buffer of 32-bit unsigned RGBA pixels.
              const off_t  i,    // offset to write to framebuffer.
              const size_t size) // The size in bytes to write.
              const 
              noexcept
{
    // Check if size of read is out of range.
    if (size > this->size())
        return -EINVAL; // Invalid parameter.

    // Open framebuffer file.
    fb         fb;

    // Get screen attributes.
    const auto v = fb.sc.vinfo(); // Get "variable" screen info.
    const auto s = start(v);       // Compute the start index of the window position.

    // Copy row by row.
    for (uint y = 0; y < rcur.h; ++y)
        memcpy(rcast<u32*>(buf) + (y * rcur.w), &fb.get32(s + i + (y * v.xres)), rcur.w * sizeof(u32));

/*
    // Get screen attributes.
    const auto v = fb.sc.vinfo();
    const auto s = pcur.x + pcur.y * v.xres;

    // Get width of the rectangle to read.
    const auto w = this->rcur.w;

    // TODO: Read framebuffer, convert and copy the pixels into the buffer provided by the caller.
    for (size_t y = 0; y < rcur.h; ++y) {
        for (size_t x = 0; x < rcur.w; ++x) {
            u32* p = rcast<u32*>(buf);
            // TODO: Convert framebuffer pixel into 32-bit RGBA pixel.
        }
    }
*/
    return 0; // Operation succeeded.
}

// Write to the picture buffer to the rectangle. Returns exactly the number of bytes written except on error.
int wnd::write(const void  *buf,  // Buffer of 32-bit unsigned RGBA pixels.
               const off_t  i,    // offset to write to framebuffer.
               const size_t size) // The size in bytes to write.
               noexcept
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

    // Copy row by row.
    for (uint y = 0; y < rcur.h; ++y)
        memcpy(&fb.get32(s + i + (y * v.xres)), rcast<const u32*>(buf) + (y * rcur.w), rcur.w*sizeof(u32));

/*
    // Convert pixels in the given buffer and write it to the framebuffer file.
    const auto w = this->rcur.w;
    for (uint y = 0; y < rcur.h; ++y) {
        for (uint x = 0; x < rcur.w; ++x) {
            // Assume 32-bit unsigned RGBA pixels.
            const u32* p = rcast<const u32*>(buf);
            uint       r = p[0+x+y*w], // 32-bit red.
                       g = p[1+x+y+w], // 32-bit green.
                       b = p[2+x+y+w], // 32-bit blue.
                       a = p[3+x+y+w]; // 32-bit alpha-transparency.
            fb.set(s+x+y*v.xres, Pix(r, g, b, a));
        }
    }
*/

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
