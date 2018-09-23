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
#include "dsys.hpp"

// Display system.
namespace {
#if defined(DRM)
    // TODO: Use DRM graphical output.
#elif defined(FB)
    // Use framebuffer graphical output.
    fb *f;
#endif
}

	// Bit depths of color components.
uint dsys::red,   // Bit depth of the red component.
     dsys::green, // Bit depth of the green component.
     dsys::blue,  // Bit depth of the blue component.
     dsys::alpha; // Bit depth of the alpha component.

// Initialize display system.
void dsys::init() 
{
#if defined(DRM)
    drm::init();
#elif defined(FB)
    // Allocate framebuffer.
    f    = new fb();
    // Set color bit depths.
    red   = f->roff;
    green = f->goff;
    blue  = f->boff;
    alpha = f->aoff;
#endif
}

// Write to display screen.
void dsys::write(const char  *name, // Name of the display screen.
                 const char  *buf,  // Buffer to write to the display screen.
                 const off_t  i,    // Offset of the display.
                 const size_t size) // How much in bytes to write to the display screen.
{
#ifdef FB
    memcpy(&f->get8(i), buf, size);
#elif DRM
#   error Write unimplemented for DRM.
#endif
}

// Read from display screen.
void dsys::read(const char  *name, // Name of the display screen.
                char        *buf,  // Buffer to read to.
                const off_t  i,    // Offset to read from.
                const size_t size) // How much in bytes to read from the display screen.
{
#ifdef FB
    memcpy(buf, &f->get8(i), size);
#elif DRM
#   error Read unimplemented for DRM.
#endif
}

// De-initialize display system.
void dsys::deinit() {
#ifdef FB
    delete f;
    red = green = blue = alpha = 0;
#elif DRM
    drm::deinit();
#endif
}
