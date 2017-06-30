#include <vector>
#include <cstring>
#include <sys/mman.h>
#include "fb.hpp"
#include "log.hpp"
using namespace std;

namespace {
    vector<u8> dbuf; // Double buffer for tear-free framebuffer manipulation.
};

// Setup framebuffer file mapping to the address space.
Fb::Fb() 
    : roff(-1), goff(-1), boff(-1), aoff(-1)
{
    // Get size of framebuffer in bytes.
    size = scr.finfo().smem_len;
    // Compute number of pixels.
    plen = size / sizeof(u32);
    // Set size of the double buffer to be the same as the framebuffer size in bytes.
    dbuf.resize(size);
    // Map framebuffer to computer's address space.
    fb = scast<u8*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, scr.fd, 0));
    // Set the positions to the color bits.
    const auto v = scr.vinfo();
    if (v.red.length)
        roff = v.red.offset;    // Position to red bits.
    if (v.green.length)
        goff = v.green.offset;  // Position to green bits.
    if (v.blue.length)
        boff = v.blue.offset;   // Position to blue bits.
    if (v.transp.length)
        aoff = v.transp.offset; // Position to alpha-transparency bits.
}

// Unmap framebuffer from the system address space.
Fb::~Fb() 
{
    // Unmap framebuffer.
    if (munmap(fb, size) == -1)
        die("Failed to unmap the framebuffer from the system's address space!");
}

// Access framebuffer memory 8 bits at a time.
u8& Fb::get8(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes.
{
    return dbuf[i];
}

// Access framebuffer memory 32 bits at a time.
u32& Fb::get32(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes. 
{
    return *(rcast<u32*>(dbuf.data()) + i);
}

// Get size in bytes of the framebuffer.
size_t Fb::len() const 
{
    return size;
}

// TODO: Fill a box in the framebuffer.
void Fb::boxfill(const char *buf, // Buffer.
                 const uint  w,   // Width.
                 const uint  h)   // Height.
{
    for (uint i = 0; i < h; ++i)
        rowfill(buf+i, i, w);
}

// TODO: Fill a row of pixels.
void Fb::rowfill(const char *buf, // Buffer.
                 const uint  row, // The index to the row to fill.
                 const uint  len) // The length of the row.
{
    // TODO: memcpy.
}

// Get size in pixels of the framebuffer.
size_t Fb::pixlen() const
{
    return plen;
}

// Set color value in the framebuffer.
void Fb::set(const uint i, // Index to set the color value to.
             const Col& c) // Color to set.
{
    get32(i) = c.val(roff, goff, boff, aoff);
}

// Copy double buffer into the framebuffer.
void Fb::blit()
{
    // Wait for vertical sync before copying.
    scr.vsync();

    // Blit!
    memcpy(fb, dbuf.data(), size);
}

// Clear/blacken the entire screen.
void Fb::clear()
{
    //memset(fb, 0, size);
    fill(begin(dbuf), end(dbuf), 0);
}
