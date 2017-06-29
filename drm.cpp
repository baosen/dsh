#include <xf86drm.h>
#include "types.hpp"

// DRM system.
namespace {
    int fd = -1; // File descriptor to DRM device.

    // DRM instance.
    struct Drminst {
        drmModeRes       *resources;
        drmModeConnector *connector;
        drmModeEncoder   *encoder;
    }
}

// Initialize the direct rendering manager.
void drm::init() 
{
    Drminst inst;
    zero(inst);
    if (fd = open(path, O_RDWR) == -1)
        // TODO: Warn about this error here.
        throw errno; 
}

// Deinitialize the direct rendering manager.
void drm::deinit() 
{
    if (close(fd) == -1)
        die("Failed to close the direct rendering manager!");
}
