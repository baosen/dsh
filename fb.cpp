#include <sys/mman.h>
#include "fb.hpp"
#include "log.hpp"

// Setup framebuffer file mapping to the address space.
Fb::Fb() {
    // Get size of framebuffer in bytes.
    size = scr.finfo().smem_len;
    // Map framebuffer to computer's address space.
    fb = scast<u8*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, scr.fd, 0));
    const auto v = scr.vinfo();
    roff = v.red.offset;
    goff = v.green.offset;
    boff = v.blue.offset;
    aoff = v.transp.offset;
}

// Unmap framebuffer from the system address space.
Fb::~Fb() {
    if (munmap(fb, size) == -1)
        die("Failed to unmap the framebuffer from the system's address space!");
}

// Access framebuffer memory 8 bits at a time.
u8& Fb::get8(const uint i) // Index beginning at 0 indexiing a string of framebuffer bytes.
{
    return fb[i];
}

// Access framebuffer memory 32 bits at a time.
u32& Fb::get32(const uint i) 
{
    return *(rcast<u32*>(fb)+i);
}

// Get size in bytes of the framebuffer.
size_t Fb::len() const 
{
    return size;
}

// Set color value in the framebuffer.
void Fb::set(const uint i, const Col& c)
{
    get32(i) = c.val(roff, goff, boff, aoff);
}
