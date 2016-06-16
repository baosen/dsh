#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "log.hpp"

class Pixel {
};

typedef Byte char;

class Framebuffer {
public:
    Framebuffer()
    {
        open_framebuffer_file();
        setup_screen_resolution();
        framebuffer = map_framebuffer();
    }

    Byte& get_pixel(const unsigned int x, const unsigned int y)
    {
        // TODO: Error check?
        return framebuffer[x + (y * width_resolution_in_pixels)];
    }

    ~Framebuffer()
    {
        // Unmap framebuffer from the address space.
        munmap(framebuffer, framebuffer_size);

        // Close the framebuffer file descriptor.
        if (close(framebuffer_file_descriptor) == -1) {
            die("Failed to close framebuffer 0!");
        }
    }

private:
    auto get_variable_screen_info()
    {
        fb_var_screeninfo variable_screeninfo;

        if (ioctl(framebuffer_file_descriptor, FBIOGET_VSCREENINFO, &variable_screeninfo)) {
            die("Can't read video screen information.");
        }

        return variable_screeninfo;
    }

    auto get_fixed_screen_info()
    {
        fb_fix_screeninfo fixed_screeninfo;

        if (ioctl(framebuffer_file_descriptor, FBIOGET_FSCREENINFO, &fixed_screeninfo)) {
            die("Can't read fixed screen information.");
        }

        return fixed_screeninfo;
    }

    char* map_framebuffer()
    {
        framebuffer_size = get_fixed_screen_info().smem_len;
        return static_cast<char*>(mmap(0, framebuffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer_file_descriptor, 0));
    }

    void open_framebuffer_file()
    {
        framebuffer_file_descriptor = open("/dev/fb0", O_RDWR);

        if (framebuffer_file_descriptor == -1) {
            die("Cannot open framebuffer 0!");
        }
    }

    void setup_screen_resolution()
    {
        const auto variable_info    = get_variable_screen_info();
        width_resolution_in_pixels  = variable_info.xres;
        height_resolution_in_pixels = variable_info.yres;
    }

    int framebuffer_file_descriptor;

    unsigned int width_resolution_in_pixels,
            height_resolution_in_pixels;

    char*  framebuffer = nullptr;
    size_t framebuffer_size = 0;
};
