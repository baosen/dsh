#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "log.hpp"
#include "fb.hpp"

Fb::Fb() {
    open();
    setup();
    fb = map();
}

// Open the framebuffer file descriptor.
void Fb::open() {
    fd = ::open("/dev/fb0", O_RDWR);
    if (fd == -1)
        throw err("Cannot open fb 0!");
}

// Setup framebuffer.
void Fb::setup() {
    const auto v = vinfo();
    w = v.xres; h = v.yres;
}

// Map fraembuffer to address space.
char* Fb::map() {
    size = finfo().smem_len;
    return scast<char*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
}

// Returns framebuffer variable screen info.
auto Fb::vinfo() {
    fb_var_screeninfo v;
    if (ioctl(fd, FBIOGET_VSCREENINFO, &v))
        throw err("Can't read video screen information.");
    return v;
}

// Returns framebuffer fixed screen info.
auto Fb::finfo() {
    fb_fix_screeninfo f;
    if (ioctl(fd, FBIOGET_FSCREENINFO, &f))
        throw err("Can't read fixed screen information.");
    return f;
}

// Assign a pixel to (x, y) in the framebuffer.
char& Fb::operator()(const Pos& p) {
    const int i = p.x + (p.y * w);
    if (i >= w * h)
        throw 1;
    return fb[i];
}

// Unmap framebuffer from address space.
Fb::~Fb() {
    munmap(fb, fb_size);
    if (close(fd) == -1)
        die("Failed to close fb 0!");
}
