#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "log.hpp"

namespace dshell {
    class Fb {
    public:
        Fb() {
            fd = open("/dev/fb0", O_RDWR);
            if (fd == -1)
                die("Cannot open framebuffer 0!");
    
            struct fb_var_screeninfo vinfo;
            if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo))
                die("Error reading video screen information.");
            xres = vinfo.xres;
    
            struct fb_fix_screeninfo finfo;
            if (ioctl(fd, FBIOGET_FSCREENINFO, &finfo))
                die("Error reading fixed screen information.");
    
            size = finfo.smem_len;
            fbp = (char*)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        }
    
        char& operator()(const unsigned int x, const unsigned int y) {
            // TODO: Error check?
            return fbp[x + (y * xres)];
        }
    
        ~Fb() {
            munmap(fbp, size);
            if (close(fd) == -1)
                die("Failed to close framebuffer 0!");
        }
    private:
        int fd;
        unsigned int xres;
        long int size;
        char *fbp;
    };
}
