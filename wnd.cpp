#include "wnd.hpp"
#include "fb.hpp"
using namespace std;

// Create an empty rectangular window in the framebuffer.
Wnd::Wnd() {}

// Create a rectangular window in the framebuffer.
Wnd::Wnd(const Pos& p, // The position to place the rectangle in the framebuffer.
         const Res& r) // The resolution of the rectangle in the framebuffer.
    : pcur(p), rcur(r) {}

// Computes the index of its position in the framebuffer.
uint Wnd::i() const 
{
    return pcur.i(rcur.w);
}

// Compute start index position.
uint Wnd::start(const Scr::varinfo& v) const
{
    return pcur.x + pcur.y * v.xres; // The start index of the position.
}

Off Wnd::off() const
{
    // Set the positions to the color bits.
    Fb fb;
    const auto v = fb.scr.vinfo();
    Off o;
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
void Wnd::fill(const Pix& c) // Colour to fill the inside of the rectangle with.
               const 
{
    // Open framebuffer.
    Fb fb;

    // Compute pixel color and position.
    const auto v = fb.scr.vinfo();
    const auto s = start(v); // The start index of the position.

    // Fill the rectangle in Linux framebuffer.
    for (size_t y = 0; y < rcur.h; ++y)
        for (size_t x = 0; x < rcur.w; ++x)
            fb.set(s + x + (y * v.xres), c);

    // Show it to the user!
    fb.flip();
}

// Get the size/length in bytes of the rectangular window.
size_t Wnd::size() const 
{
    return rcur.h * rcur.w;
}

// Returns the window's current position.
Pos Wnd::pos() const
{
    return pcur;
}

// Resize the rectangular window image in the framebuffer.
void Wnd::resize(const Res& newr) // The new window resolution to resize to.
{
    rcur = newr;
}

// Maximize the rectangular window image to fill the screen.
void Wnd::max() 
{
    // Save old positions before maximizing.
    save();

    // Open framebuffer file.
    Fb fb;

    // Resize the window to fill the entire screen.
    const auto v = fb.scr.vinfo();
    pcur = Pos(0, 0);
    resize(Res(v.xres, v.yres));
}

// Read from the image buffer of the rectangular window.
int Wnd::read(char  *buf,  // Buffer of 32-bit unsigned RGBA pixels.
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

    // Copy the image to the application.
    memcpy(buf, &fb.get8(i), size);

/*
    // Get screen attributes.
    const auto v = fb.scr.vinfo();
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
int Wnd::write(const char *buf,  // Buffer of 32-bit unsigned RGBA pixels.
               off_t       i,    // Offset to write to framebuffer.
               size_t      size) // The size in bytes to write.
               noexcept
{
    // Check if size of the image to be written is larger than the image itself.
    //if (size > this->size())
        //return -EINVAL; // Invalid parameter.

    // Open framebuffer file.
    Fb fb;

    // Get screen attributes.
    const auto v = fb.scr.vinfo(); // Get "variable" screen info.
    const auto s = start(v);       // Compute the start index of the window position.

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
void Wnd::save() 
{
    // Save current rectangle.
    rold = rcur;
    pold = pcur;
}
