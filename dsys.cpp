#include <cstring>
#include "dsys.hpp"
using namespace std;

// DEBUG.
#define FB

namespace {
#if defined(DRM)
    // Use DRM graphical output.
#elif defined(FB)
    // Use framebuffer graphical output.
    Fb *fb;
#else
#   error No screen output chosen. Choose one to continue compiling.
#endif
}

// Initialize display system.
void dsys::init() {
    fb = new Fb();
}

// Copy data in buffer into framebuffer.
void dsys::copy(const char *buf, const off_t i, const size_t size) {
#if defined(FB)
    memcpy(&fb->get8(i), buf, size);
#else
#   error No screen output chosen. Choose one to continue compiling.
#endif
}

// De-initialize display system.
void dsys::deinit() {
    delete fb;
}
