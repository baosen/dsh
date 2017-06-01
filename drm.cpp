#include <xf86drm.h>
#include <xf86drmMode.h>

namespace {
    int drmfd = -1;
}

// Initialize Direct-Rendering Manager.
static void init() {
    static const char *modules[] = {
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
    drmModeRes       *resources = nullptr;
    drmModeConnector *connector = nullptr;
    drmModeEncoder   *encoder   = nullptr;

    for (size_t i = 0; i < NSIZE(modules); i++) {
        printf("Loading module %s...", modules[i]);
        drmfd = drmOpen(modules[i], nullptr);
        if (drmfd < 0)
            printf("Failed to load module: %s\n", modules[i]);
        else {
            printf("Succeeded to load module: %s\n", modules[i]);
            break;
        }
    }

}

// De-initialize Direct-Rendering Manager.
static void deinit() {
    drmClose(drmfd);
}
