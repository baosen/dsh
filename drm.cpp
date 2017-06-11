#include <xf86drm.h>
#include <xf86drmMode.h>

namespace {
    int drmfd = -1;
}

// Initialize Direct-Rendering Manager.
void drm::init() {
    drmModeRes       *resources = nullptr;
    drmModeConnector *connector = nullptr;
    drmModeEncoder   *encoder   = nullptr;

    // Load a DRM module in the list below.
    static const char *mod[] = {
        "exynos",
        "i915",
        "msm",
        "nouveau",
        "omapdrm",
        "radeon",
        "tegra",
        "vc4",
        "virtio_gpu",
        "vmwgfx",
    };
    for (size_t i = 0; i < NSIZE(mod); i++) {
        printf("Loading module %s...", mod[i]);
        drmfd = drmOpen(mod[i], nullptr);
        if (drmfd < 0)
            printf("Failed to load module: %s\n", mod[i]);
        else {
            printf("Succeeded to load module: %s\n", mod[i]);
            break;
        }
    }

}

// Deinitialize the direct rendering manager.
void drm::deinit() {
    drmClose(drmfd);
}
