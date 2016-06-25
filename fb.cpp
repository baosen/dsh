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

void Fb::setup() {
    const auto v = vinfo();
    width = v.xres;
    height = v.yres;
}

void Fb::open() {
    fbfd = open("/dev/fb0", O_RDWR);

    if (fbfd == -1)
        die("Cannot open fb 0!");
}

char* Fb::map() {
    size = finfo().smem_len;
    return (char*)(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0));
}

auto Fb::vinfo() {
    fb_var_screeninfo vinfo;

    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo))
        die("Can't read video screen information.");

    return vinfo;
}

auto Fb::finfo() {
    fb_fix_screeninfo finfo;

    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo))
        die("Can't read fixed screen information.");

    return finfo;
}

char& Fb::operator()(const unsigned int x, const unsigned int y) {
    // TODO: Error check?
    return fb[x + (y * widthres)];
}

Fb::~Fb() {
    munmap(fb, fb_size);

    if (close(fbfd) == -1)
        die("Failed to close fb 0!");
}
