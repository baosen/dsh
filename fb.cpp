#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <cstring>
#include "types.hpp"
#include "log.hpp"
#include "rect.hpp"
#include "fb.hpp"

// Setup framebuffer file.
Fb::Fb() {
    openfb();
    setup();
    fb = map();
}

// Unmap framebuffer from address space.
Fb::~Fb() {
    munmap(fb, size);
    if (close(fd) == -1)
        die("Failed to close /dev/fb0!");
}

// Open the framebuffer file descriptor.
void Fb::openfb() {
    fd = ::open("/dev/fb0", O_RDWR);
    if (fd == -1)
        throw err("Cannot open /dev/fb0!");
}

// Returns framebuffer variable screen info.
fb_var_screeninfo Fb::vinfo() {
    fb_var_screeninfo v;
    if (ioctl(fd, FBIOGET_VSCREENINFO, &v))
        throw err("Can't read video screen information.");
    return v;
}

// Returns framebuffer fixed screen info.
fb_fix_screeninfo Fb::finfo() {
    fb_fix_screeninfo f;
    if (ioctl(fd, FBIOGET_FSCREENINFO, &f))
        throw err("Can't read fixed screen information.");
    return f;
}

// Setup framebuffer.
void Fb::setup() {
    const auto v = vinfo();
    printf("Original %dx%d, %dbpp\n", v.xres, v.yres, v.bits_per_pixel);
    w = v.xres;
    h = v.yres;
    bpp = v.bits_per_pixel;
}

// Map fraembuffer to address space.
char* Fb::map() {
    size = finfo().smem_len;
    return scast<char*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
}

// Assign a pixel to (x, y) in the framebuffer.
char& Fb::operator()(const Pos& p) {
    const int i = p.i(w);
    if (i >= w*h)
        throw 1;
    return fb[i];
}

// Fill a  rectangle with a color.
void Fb::fill(const Rect& r, const uint c) {
    const int i = r.i();
    if (i >= w*h)
        throw 1;
    memset(fb+i, c, r.size());
}

void Fb::fill(const uint c) {
    memset(fb, c, w*h*(bpp/8));
}
