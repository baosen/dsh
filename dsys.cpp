// DEBUG.
#define FB

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
void dsys::init() {
#if defined(DRM)
    drm::init();
#elif defined(FB)
    fb = new Fb();
#endif
}

// Copy data in buffer into framebuffer.
void dsys::write(const char *name, const char *buf, const off_t i, const size_t size) {
#ifdef FB
    memcpy(&fb->get8(i), buf, size);
#endif
}

void dsys::read(const char* name, char *buf, const off_t i, const size_t size) {
#ifdef FB
    memcpy(buf, &fb->get8(i), size);
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
