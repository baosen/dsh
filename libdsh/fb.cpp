#include <cstdarg>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include "types.hpp"
#include "log.hpp"
#include "rect.hpp"
#include "fb.hpp"
#include "col.hpp"

// Open the framebuffer file.
Scr::Scr() {
    fd = ::open("/dev/fb0", O_RDWR);
    if (fd == -1)
        throw err("Cannot open /dev/fb0!");
    // Setup screen.
    const auto v = vinfo();
    w   = v.xres;
    h   = v.yres;
    bpp = v.bits_per_pixel;
    printf("Screen resolution: %ux%u, %ubpp\n", v.xres, v.yres, v.bits_per_pixel);
    roff = v.red.offset;
    goff = v.green.offset;
    boff = v.blue.offset;
    aoff = v.transp.offset;
    printf("Offset: R%u, G%u, B%u, A%u\n", roff, goff, boff, aoff);
    rl = v.red.length; 
    gl = v.green.length; 
    bl = v.blue.length; 
    al = v.transp.length;
    printf("Color: RGBA_%u%u%u%u\n", rl, gl, bl, al);
}

// Close framebuffer file.
Scr::~Scr() {
    if (close(fd) == -1)
        die("Failed to close /dev/fb0!");
}

// Control screen.
int Scr::ctl(unsigned long req, ...) {
    va_list a;
    va_start(a, req);
    ioctl(fd, req);
    va_end(a);
}

// Map framebuffer to computer's address space.
Ptr Scr::map() {
    Ptr(*this);
}

// Returns framebuffer variable screen info.
Scr::varinfo Scr::vinfo() {
    varinfo v;
    if (ctl(FBIOGET_VSCREENINFO, &v))
        throw err("Can't read video screen information.");
    return v;
}

// Returns framebuffer fixed screen info.
Scr::fixinfo Scr::finfo() {
    fixinfo f;
    if (ctl(FBIOGET_FSCREENINFO, &f))
        throw err("Can't read fixed screen information.");
    return f;
}

// Setup framebuffer file.
Fb::Fb() {
    fb = scr.map();
}

// Unmap framebuffer from address space.
Fb::~Fb() {
    // TODO:
}

// Assign a pixel to (x, y) in the framebuffer.
char& Fb::operator()(const Pos& p) {
    const auto i = p.i(w);
    if (i >= w*h)
        throw Fb::Err::OOR;
    return rcast<char*>(fb)[i];
}

// Fill a rectangle with a color.
void Fb::fill(const Rect& r, const Col& c) {
    if (r.i() >= w*h)
        throw Fb::Err::OOR;
    r.fill(*this, c);
}

// Fill the entire screen with a color.
void Fb::fill(const Col& c) {
    const auto p = c.val(roff, goff, boff);
    for (size_t i = 0; i < w*h; ++i)
        *((scast<u32*>(fb))+i) = p;
}
