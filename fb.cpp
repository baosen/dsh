#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <cstring>
#include "types.hpp"
#include "log.hpp"
#include "rect.hpp"
#include "fb.hpp"

namespace {
    int fd;
    uint w, h;
    char*  fb;
    size_t size;

    // Open the framebuffer file descriptor.
    void openfb() {
        fd = ::open("/dev/fb0", O_RDWR);
        if (fd == -1)
            throw err("Cannot open fb 0!");
    }

    // Returns framebuffer variable screen info.
    fb_var_screeninfo vinfo() {
        fb_var_screeninfo v;
        if (ioctl(fd, FBIOGET_VSCREENINFO, &v))
            throw err("Can't read video screen information.");
        return v;
    }
    
    // Returns framebuffer fixed screen info.
    fb_fix_screeninfo finfo() {
        fb_fix_screeninfo f;
        if (ioctl(fd, FBIOGET_FSCREENINFO, &f))
            throw err("Can't read fixed screen information.");
        return f;
    }
    
    // Setup framebuffer.
    void setup() {
        const auto v = vinfo();
        w = v.xres; h = v.yres;
    }
    
    // Map fraembuffer to address space.
    char* map() {
        size = finfo().smem_len;
        return scast<char*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    }
}

Fb::Fb() {
    openfb();
    setup();
    fb = map();
}

// Unmap framebuffer from address space.
Fb::~Fb() {
    munmap(fb, size);
    if (close(fd) == -1)
        die("Failed to close fb 0!");
}

// Assign a pixel to (x, y) in the framebuffer.
char& Fb::operator()(const Pos& p) {
    const int i = p.i(w);
    if (i >= w * h)
        throw 1;
    return fb[i];
}

// Fill a  rectangle with a color.
void Fb::fill(const Rect& r, const int c) {
    const int i = r.i();
    if (i >= w*h)
        throw 1;
    memset(fb+i, c, r.size());
}
