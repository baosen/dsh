#include <memory>
#include "fb.hpp"
#include "dpysys.hpp"
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
//#   error No screen output chosen. Choose one to continue compiling.
#endif
}

// Initialize display system.
void dpysys::init() {
    fb = new Fb();
}

// De-initialize display system.
void dpysys::deinit() {
    delete fb;
}
