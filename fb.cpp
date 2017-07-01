#include <cstring>
#include <sys/mman.h>
#include "fb.hpp"
#include "log.hpp"
using namespace std;

// Setup framebuffer file mapping to the address space.
Fb::Fb() 
    : roff(-1), goff(-1), boff(-1), aoff(-1), // Blanken color offsets.
      vsyncen(true)                           // Enable vertical sync.
{
    // Check if double buffer using double height of virtual screen is setup.
    if (scr.dbufen) {
        // Get size of framebuffer in bytes and half it to accommedate for the virtual screen.
        size = scr.finfo().smem_len / 2;
    } else {
        // Get size of framebuffer in bytes.
        size = scr.finfo().smem_len;
        // Set size of the double buffer to be the same as the framebuffer size in bytes.
        dbuf.resize(size);
    }

    // Compute number of pixels.
    plen = size / sizeof(u32);

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

    // Try waiting for vertical sync to check if it is available.
    this->vsync();
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

// Get size in pixels of the framebuffer.
size_t Fb::pixlen() const
{
    return plen;
}

// Copy provided buffer to this framebuffer.
void Fb::copy(const uint i, const char *buf, const size_t len)
{
    // TODO: Double buffer.
    memcpy(fb+i, buf, len);
}

// Set color value in the framebuffer.
void Fb::set(const uint i, // Index to set the color value to.
             const Pix& c) // Color to set.
{
    get32(i) = c.val(roff, goff, boff, aoff);
}

// Wait for vertical sync.
void Fb::vsync()
{
    // Try waiting for vertical sync.
    try {
        scr.vsync();
    } catch (const err& e) {
        // Disable vertical sync, because it is not supported.
        vsyncen = false;
    }
}

// Flip between two buffers, thus reduce tearing.
void Fb::flip()
{
    // Wait for vertical sync before copying.
    if (vsyncen) // Check if vertical sync is enabled.
        vsync();

    // Blit by copying the double buffer into the framebuffer.
    if (scr.dbufen) {
        scr.flip();
        // TODO: Change pointer.
    } else {
        memcpy(fb, dbuf.data(), size);
    }
}

// Clear/blacken the entire screen.
void Fb::clear()
{
    //memset(fb, 0, size);
    fill(begin(dbuf), end(dbuf), 0);
}
