#include <cstring>
#include <sys/mman.h>
#include "types.hpp"
#include "rect.hpp"
#include "fb.hpp"
#include "col.hpp"

// Setup framebuffer file.
Fb::Fb() {
    // Map framebuffer to computer's address space.
    size = scr.finfo().smem_len;
    fb = scast<char*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, scr.fd, 0));
}

// Unmap framebuffer from address space.
Fb::~Fb() {
    if (munmap(fb, size) == -1) {
        perror("Error");
        exit(errno);
    }
}

// Access its memory.
char& Fb::operator[](const uint i) {
    return fb[i];
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
