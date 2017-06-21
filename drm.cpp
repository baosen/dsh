#include <xf86drm.h>

namespace {
    int fd = -1;
}

// Initialize Direct-Rendering Manager.
void drm::init(const char *path) {
    drmModeRes       *resources = nullptr;
    drmModeConnector *connector = nullptr;
    drmModeEncoder   *encoder   = nullptr;

    if (fd = open(path, O_RDWR) == -1)
        throw errno; // TODO!
}

// Deinitialize the direct rendering manager.
void drm::deinit() {
    close(fd);
}
