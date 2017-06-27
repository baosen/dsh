#include <xf86drm.h>
#include "types.hpp"

namespace {
    int fd = -1;

    // DRM instance.
    struct Drminst {
        drmModeRes       *resources;
        drmModeConnector *connector;
        drmModeEncoder   *encoder;
    }
}

// Initialize Direct-Rendering Manager.
void drm::init(const char *path) {
    Drminst inst;
    zero(inst);
    if (fd = open(path, O_RDWR) == -1)
        throw errno; // TODO!
}

// Deinitialize the direct rendering manager.
void drm::deinit() {
    if (close(fd) == -1)
        die("Failed to close DRM!");
}
