#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "log.hpp"

template<int nrows, int ncols>
class Vec<nrows, ncols> {
};

class Fb {
public:
    Fb()
    {
        // Setup the fb.
        open_fb_file();
        setup_screen_resolution();
        fb = map();
    }

    char& operator()(const unsigned int x, const unsigned int y)
    {
        // TODO: Error check?
        return fb[x + (y * widthres)];
    }

    ~Fb()
    {
        // Unmap fb from the address space.
        munmap(fb, fb_size);

        // Close the fb file descriptor.
        if (close(fbfd) == -1)
            die("Failed to close fb 0!");
    }

private:
    auto get_vinfo()
    {
        fb_var_screeninfo vinfo;

        if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo))
            die("Can't read video screen information.");

        return vinfo;
    }

    auto getfinfo()
    {
        fb_fix_screeninfo finfo;

        if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
            die("Can't read fixed screen information.");
        }

        return finfo;
    }

    char* map()
    {
        fb_size = getfinfo().smem_len;
        return static_cast<char*>(mmap(nullptr, fb_size, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0));
    }

    void open_fb_file()
    {
        fbfd = open("/dev/fb0", O_RDWR);

        if (fbfd == -1)
            die("Cannot open fb 0!");
    }

    void setup_screen_resolution()
    {
        const auto v = get_vinfo();
        widthres = v.xres;
        heightres = v.yres;
    }

    int fbfd;

    unsigned int widthres, heightres;

    char*  fb = nullptr;
    size_t fb_size = 0;
};
