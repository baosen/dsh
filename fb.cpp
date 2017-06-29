#include <sys/mman.h>
#include "fb.hpp"
#include "log.hpp"

// Setup framebuffer file mapping to the address space.
Fb::Fb() 
{
    // Get size of framebuffer in bytes.
    size = scr.finfo().smem_len;
    // Map framebuffer to computer's address space.
    fb = scast<u8*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, scr.fd, 0));
    // Set the positions to the color bits.
    const auto v = scr.vinfo();
    roff = v.red.offset;    // Position to red bits.
    goff = v.green.offset;  // Position to green bits.
    boff = v.blue.offset;   // Position to blue bits.
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

// Set color value in the framebuffer.
void Fb::set(const uint i, // Index to set the color value to.
             const Col& c) // Color to set.
{
    get32(i) = c.val(roff, goff, boff, aoff);
}
