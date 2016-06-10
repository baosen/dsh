#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "log.hpp"
using namespace dshell;

namespace {
    int          framebuf_file_desc;

    unsigned int width_of_screen_in_px, 
                 height_of_screen_in_px;

    char*        framebuffer;
    long int     framebuffer_size;

    char* map_framebuffer_to_memory() {
        return static_cast<char*>(mmap(0, framebuffer_size, 
                                          PROT_READ | PROT_WRITE, 
                                          MAP_SHARED, framebuf_file_desc, 0));
    }
}

void init_framebuffer() {
    framebuf_file_desc = open("/dev/fb0", O_RDWR);
    if (framebuf_file_desc == -1)
        die("Cannot open framebuffer 0!");

    struct fb_var_screeninfo vinfo;
    if (ioctl(framebuf_file_desc, FBIOGET_VSCREENINFO, &vinfo))
        die("Can't read video screen information.");
    width_of_screen_in_px = vinfo.xres;
    height_of_screen_in_px = vinfo.yres;

    struct fb_fix_screeninfo finfo;
    if (ioctl(framebuf_file_desc, FBIOGET_FSCREENINFO, &finfo))
        die("Can't read fixed screen information.");

    framebuffer_size = finfo.smem_len;
    framebuffer = map_framebuffer_to_memory();
}

char& get(const uint x, const uint y) {
    // TODO: Error check?
    return framebuffer[x + (y * width_of_screen_in_px)];
}

uint maxw() {
    return width_of_screen_in_px;
}

uint maxh() {
    return height_of_screen_in_px;
}

void destroy_framebuffer() {
    munmap(framebuffer, framebuffer_size);
    if (close(framebuf_file_desc) == -1)
        die("Failed to close framebuffer 0!");
}
