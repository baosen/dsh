#include "config.hpp"
#include <EGL/egl.h>
#include <gbm.h>
#include "gbm.hpp"
#include "fio.hpp"
#include "log.hpp"

namespace {
    EGLDisplay  egldisp; // OpenGL ES display.
    gbm_device *gbmdev;  // "Generic buffer management"-device by Mesa.
}

// Initialize Mesa's generic buffer management.
void gbm::init()
{
    // Open DRI file.
    const auto fd = open(CARD0_PATH, 
                         O_RDWR | FD_CLOEXEC); // Read/Write and close on execute succeed.
    if (fd < 0)
        die("Failed to open " CARD0_PATH "!");

    // Create generic buffer manager device.
    gbmdev = gbm_create_device(fd);
    if (!gbmdev)
        die("Failed to create a GBM device.");

#ifdef EGL_MESA_platform_gbm
    egldisp = eglGetPlatformDisplayEXT(EGL_PLATFORM_GBM_MESA, gbm, nullptr);
#else
    egldisp = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#endif

    // Check if we found a display.
    if (egldisp == EGL_NO_DISPLAY)
        die("Found no EGL display.");

    // The version of the EGL API set by eglInitialize().
    EGLint major, // Major version number.
           minor; // Minor version number.

    // Initialize embedded OpenGL.
    if (!eglInitialize(egldisp, &major, &minor))
        die("Failed to initialize EGL!");
}

// Configure GBM.
void config()
{
    EGLint attribs[] {
        EGL_BUFFER_SIZE,     32,
        EGL_DEPTH_SIZE,      EGL_DONT_CARE,
        EGL_STENCIL_SIZE,    EGL_DONT_CARE,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
        EGL_NONE,
    };

    // Get EGL configurations.
    EGLint n;
    if (!eglGetConfigs(egldisp, nullptr, 0, &n))
        die("Failed to get EGL configurations.");

    // Allocate EGL configuration.
    EGLConfig *configs = malloc(n * sizeof(EGLConfig));
    if (!eglChooseConfig(egldisp, attribs, configs, n, &n)) {
        free(configs);
        die("Failed to choose EGL configuration.");
    }
    if (!n) {
        free(configs);
        die("No EGL configuration exists.");
    }

    // Find a config whose native visual ID is the desired GBM format.
    for (uint i = 0; i < n; ++i) {
        EGLint fmt; // GBM surface format.
        if (!eglGetConfigAttrib(egldisp, configs[i], EGL_NATIVE_VISUAL_ID, &fmt))
            die("Failed to get a configuration attribute.");
        if (fmt == GBM_FORMAT_XRGB8888) {
            config.egl = configs[i];
            free(configs);
            return config;
        }
    }
    // Failed to find a config with a matching GBM format.
    die("Failed to find a configuration with a matching GBM format.");
}

// GL window.
struct Wnd {
    struct gbm_surface *gbm; // GBM surface.
    EGLSurface         *egl; // EGL surface.
};

// Get GBM window.
static Wnd getwnd()
{
    Wnd w;
    w.gbm = gbm_surface_create(gbm, 256, 256, GBM_FORMAT_XRGB8888, GBM_BO_USE_RENDERING);
    if (!w.gbm)
        die("Failed to get GBM surface!");

#ifdef EGL_MESA_platform_gbm
    w.egl = eglCreatePlatformWindowSurfaceEXT(egl, egl, gbm, nullptr);
#else
    w.egl = eglCreateWindowSurface(w.egl, config.egl, w.gbm, nullptr);
#endif
    if (w.egl == EGL_NO_SURFACE)
        die("No GBM surface exists!");

    return w;
}
