#include <cstring>
#include <sys/mman.h>
#include "types.hpp"
#include "rect.hpp"
#include "fb.hpp"
#include "col.hpp"

// Setup framebuffer file.
Fb::Fb() {
    // Get size of framebuffer in bytes.
    size = scr.finfo().smem_len;
    // Map framebuffer to computer's address space.
    fb = scast<u8*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, scr.fd, 0));
}

// Unmap framebuffer from address space.
Fb::~Fb() {
    if (munmap(fb, size) == -1) {
        perror("Error");
        exit(errno);
    }
}

// Access framebuffer memory 8 bits at a time.
u8& Fb::get8(const uint i) {
    return fb[i];
}

// Access framebuffer memory 32 bits at a time.
u32& Fb::get32(const uint i) {
    return *(rcast<u32*>(fb)+i);
}

/*
// Assign a pixel to (x, y) in the framebuffer.
char& Fb::operator()(const Pos& p) {
    const auto i = p.i(scr.w);
    if (i >= scr.w * scr.h)
        throw Fb::Err::OOR;
    return fb[i];
}

// Fill a rectangle in the framebuffer with a color.
void Fb::fill(const Rect& r, const Col& c) {
    if (r.i() >= scr.w * scr.h)
        throw Fb::Err::OOR;
    r.fill(fb, c);
}

// Fill the entire screen with a color.
void Fb::fill(const Col& c) {
    const auto p = c.val(scr.roff, scr.goff, scr.boff);
    for (size_t i = 0; i < scr.w*scr.h; ++i)
        fb.i32(i) = p;
}
*/
