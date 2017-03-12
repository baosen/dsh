/*
#include <xf86drm.h>

class Drm {
public:
    Drm() {
        static const char *modules[] = {
            "exynos",
            "i915",  // Intel integrated GPU.
            "msm",
            "nouveau", // Nvidia open source driver.
            "omapdrm",
            "radeon",
            "tegra",
            "vc4",
            "virtio_gpu", // Virtual GPU for virtual machines.
            "vmwgfx",
        };

        drmModeRes       *resources;
        drmModeConnector *connector = NULL;
        drmModeEncoder   *encoder = NULL;
    }
};
*/