#include <cstdlib>
#include <EGL/egl.h>
#include <gbm.h>
#include "fio.hpp"

static void check_extensions()
{
#ifdef EGL_MESA_platform_gbm
    const char *ext = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
    if (!ext)
        // EGL_EXT_client_extensions is unsupported.
        abort();
    if (!strstr(ext, "EGL_MESA_platform_gbm"))
        abort();
#endif
}

namespace {
    EGLDisplay  egl;
    gbm_device *gbm;
}

// Initialize GBM.
void init()
{
    int fd = open("/dev/dri/card0", O_RDWR | FD_CLOEXEC);
    if (fd < 0)
        abort();

    gbm = gbm_create_device(fd);
    if (!gbm)
        abort();

#ifdef EGL_MESA_platform_gbm
    egl = eglGetPlatformDisplayEXT(EGL_PLATFORM_GBM_MESA, gbm, nullptr);
#else
    egl = eglGetDisplay(gbm);
#endif
    if (egl == EGL_NO_DISPLAY)
        abort();

    EGLint major, minor;
    if (!eglInitialize(egl, &major, &minor))
        abort();
}

// Configuration.
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

    // Allocate configuration.
    EGLConfig *configs = malloc(n*sizeof(EGLConfig));
    if (!eglChooseConfig(egl, attribs, configs, n, &n))
        abort();
    if (!n)
        abort();

    // Find a config whose native visual ID is the desired GBM format.
    for (int i = 0; i < n; ++i) {
        EGLint fmt;
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

// Get GBM window.
void getwnd()
{
    window.gbm = gbm_surface_create(gbm, 256, 256, GBM_FORMAT_XRGB8888, GBM_BO_USE_RENDERING);
    if (!window.gbm)
        abort();
#ifdef EGL_MESA_platform_gbm
    window.egl = eglCreatePlatformWindowSurfaceEXT(egl, egl, gbm, nullptr);
#else
    window.egl = eglCreateWindowSurface(.egl, config.egl, window.gbm, nullptr);
#endif
    if (window.egl == EGL_NO_SURFACE)
        abort();
    return window;
}
