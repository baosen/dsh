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
    Fb *fb;
#endif
}

namespace dsys {
	// Bit depths of color components.
	uint red,   // Bit depth of the red component.
	     green, // Bit depth of the green component.
	     blue,  // Bit depth of the blue component.
	     alpha; // Bit depth of the alpha component.
}

// Initialize display system.
void dsys::init() 
{
#if defined(DRM)
    drm::init();
#elif defined(FB)
    // Allocate framebuffer.
    fb    = new Fb();
    // Set color bit depths.
    red   = fb->roff;
    green = fb->goff;
    blue  = fb->boff;
    alpha = fb->aoff;
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
    red = green = blue = alpha = 0;
#elif DRM
    drm::deinit();
#endif
}
