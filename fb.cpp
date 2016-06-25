#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "log.hpp"

Fb::Fb() {
    open();
    setup();
    fb = map();
}

// Open the framebuffer file descriptor.
void Fb::open() {
    fd = open("/dev/fb0", O_RDWR);

    if (fd == -1)
        die("Cannot open fb 0!");
}

// Setup framebuffer.
void Fb::setup() {
    const auto v = vinfo();
    width = v.xres;
    height = v.yres;
}

// Map fraembuffer to address space.
char* Fb::map() {
    size = finfo().smem_len;
    return (char*)(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
}

auto Fb::vinfo() {
    fb_var_screeninfo vinfo;

    if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo))
        die("Can't read video screen information.");

    return vinfo;
}

auto Fb::finfo() {
    fb_fix_screeninfo finfo;

    if (ioctl(fd, FBIOGET_FSCREENINFO, &finfo))
        die("Can't read fixed screen information.");

    return finfo;
}

char& Fb::operator()(const uint x, const uint y) {
    const int i = x + (y * w);

    if (i >= w * h)
        throw 1;

    return fb[i];
}

Fb::~Fb() {
    munmap(fb, fb_size);

    if (close(fd) == -1)
        die("Failed to close fb 0!");
}
