#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

namespace {
    int          framebuffer_file_descriptor;

    unsigned int width_resolution_in_pixels,
                 height_resolution_in_pixels;

    char*        framebuffer;
    long int     framebuffer_size;

    char* map_framebuffer_to_memory(const size_t framebuf_size)
    {
        framebuffer_size = framebuf_size;
        return static_cast<char*>(mmap(0, framebuffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer_file_descriptor, 0));
    }

    void open_framebuffer()
    {
        framebuffer_file_descriptor = open("/dev/fb0", O_RDWR);
        if (framebuffer_file_descriptor == -1) {
            die("Cannot open framebuffer 0!");
        }
    }

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
}

void setup_screen_resolution()
{
    const auto variable_info    = get_variable_screen_info();
    width_resolution_in_pixels  = variable_info.xres;
    height_resolution_in_pixels = variable_info.yres;
}

void setup_framebuffer()
{
    open_framebuffer();
    setup_screen_resolution();
    framebuffer = map_framebuffer_to_memory(get_fixed_screen_info().smem_len);
}

char& get(const unsigned int x, const unsigned int y)
{
    // TODO: Error check?
    return framebuffer[x + (y * width_resolution_in_pixels)];
}

unsigned int get_max_width()
{
    return width_resolution_in_pixels;
}

unsigned int get_max_height()
{
    return height_resolution_in_pixels;
}

void destroy_framebuffer()
{
    munmap(framebuffer, framebuffer_size);
    if (close(framebuffer_file_descriptor) == -1)
        die("Failed to close framebuffer 0!");
}
