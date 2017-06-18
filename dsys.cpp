#include "config.hpp"
// Use DRM graphical output.
#if defined(DRM)
#   include "drm.hpp"
// Use framebuffer graphical output.
#elif defined(FB)
#   include "fb.hpp"
#else
#   error No screen output chosen. Choose one to continue compiling.
#endif
#include <cstring>
#include "dsys.hpp"
using namespace std;

namespace {
#if defined(DRM)
    // Use DRM graphical output.
#elif defined(FB)
    // Use framebuffer graphical output.
    Fb *fb;
#endif
}

// Initialize display system.
void dsys::init() 
{
#if defined(DRM)
    drm::init();
#elif defined(FB)
    fb = new Fb();
#endif
}

// Write to display screen.
void dsys::write(const char  *name, // Name of the display screen.
                 const char  *buf,  // Buffer to write to the display screen.
                 const off_t  i,    // Offset of the display.
                 const size_t size) // How much in bytes to write to the display screen.
                 noexcept
{
#ifdef FB
    memcpy(&fb->get8(i), buf, size);
#elif DRM
#   error Write unimplemented for DRM.
#endif
}

// Read from display screen.
void dsys::read(const char  *name, // Name of the display screen.
                char        *buf,  // Buffer to read to.
                const off_t  i,    // Offset to read from.
                const size_t size) // How much in bytes to read from the display screen.
                noexcept
{
#ifdef FB
    memcpy(buf, &fb->get8(i), size);
#elif DRM
#   error Read unimplemented for DRM.
#endif
}

// De-initialize display system.
void dsys::deinit() {
#ifdef FB
    delete fb;
#elif DRM
    drm::deinit();
#endif
}
