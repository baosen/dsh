#include <cstring>
#include <sys/mman.h>
#include "fb.hpp"
#include "log.hpp"

// Setup framebuffer file mapping to the address space.
Fb::Fb() 
    : roff(-1), goff(-1), boff(-1), aoff(-1)
{
    // Get size of framebuffer in bytes.
    size = scr.finfo().smem_len;
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
    return fb[i];
}

// Access framebuffer memory 32 bits at a time.
u32& Fb::get32(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes. 
{
    return *(rcast<u32*>(fb) + i);
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

// Set color value in the framebuffer.
void Fb::set(const uint i, // Index to set the color value to.
             const Col& c) // Color to set.
{
    get32(i) = c.val(roff, goff, boff, aoff);
}

// Clear/blacken the entire screen.
void Fb::clear()
{
    memset(fb, 0, size);
}
