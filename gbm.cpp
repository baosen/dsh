#include <cstdlib>
#include <EGL/egl.h>
#include <gbm.h>
#include "fio.hpp"
#include "log.hpp"

namespace {
    void check_extensions()
    {
    #ifdef EGL_MESA_platform_gbm
        const char *ext = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
        if (!ext) // Is EGL_EXT_client_extensions is supported?
            die("EGL_EXT_client_extensions is not supported.");
        if (!strstr(ext, "EGL_MESA_platform_gbm"))
            die("EGL_MESA_platform_gbm is not supported.");
    #endif
    }

    EGLDisplay  egl; // OpenGL ES display.
    gbm_device *gbm; // "Generic buffer management"-device by Mesa.
}

// Initialize Mesa's generic buffer management.
void init()
{
    // Path to the main device card file.
    #define CARD0_PATH "/dev/dri/card0"

    const auto fd = open(CARD0_PATH, O_RDWR | FD_CLOEXEC);
    if (fd < 0)
        die("Failed to open " CARD0_PATH "!");
    gbm = gbm_create_device(fd);
    if (!gbm)
        die("Failed to create a GBM device.");
#ifdef EGL_MESA_platform_gbm
    egl = eglGetPlatformDisplayEXT(EGL_PLATFORM_GBM_MESA, gbm, nullptr);
#else
    egl = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#endif
    if (egl == EGL_NO_DISPLAY)
        die("Found no EGL display.");
    EGLint major, // Major version number.
           minor; // Minor version number.
    if (!eglInitialize(egl, &major, &minor))
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
    if (!eglGetConfigs(egl, nullptr, 0, &n))
        abort();

    // Allocate EGL configuration.
    EGLConfig *configs = malloc(n*sizeof(EGLConfig));
    if (!eglChooseConfig(egl, attribs, configs, n, &n)) {
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
        if (!eglGetConfigAttrib(egl, configs[i], EGL_NATIVE_VISUAL_ID, &fmt))
            abort();
        if (fmt == GBM_FORMAT_XRGB8888) {
            config.egl = configs[i];
            free(configs);
            return config;
        }
    }
    // Failed to find a config with matching GBM format.
    abort();
}

struct Wnd {
    struct gbm_surface *gbm; // GBM surface.
    EGLSurface  *egl; // EGL surface.
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
