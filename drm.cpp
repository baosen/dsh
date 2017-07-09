#include "config.hpp"
#include <xf86drm.h>
#include <xf86drmMode.h>
#include "types.hpp"
#include "log.hpp"
#include "zero.hpp"
#include "fio.hpp"
#include "drm.hpp"

// Direct rendering manager-system.
namespace {
    int fd = -1; // File descriptor to DRM device.

    // DRM instance.
    struct Drm {
        int               fd;        // DRM file device.
        drmModeRes       *resources; // ??
        drmModeConnector *connector; // Connector.
        drmModeEncoder   *encoder;   // Encoder.
        drmModeModeInfo  *mode;      // Mode information.
    };
}

// Initialize the Direct Rendering Manager.
void drm::init() 
{
    // Setup DRM structure.
    Drm drm;
    zero(drm);
    int i,    // index.
        area; // ??.

    // Open DRM device file.
    if ((drm.fd = ::open(CARD0_PATH, O_RDWR)) < 0)
        // TODO: Warn about this error here.
        throw errno; 

    // Get DRM mode resources.
	if (!(drm.resources = drmModeGetResources(drm.fd))) {
        syserror("Failed to get DRM mode resources!");
        throw -1;
    }

	// Find a connected connector.
	for (i = 0; i < drm.resources->count_connectors; i++) {
        // Is connector connected?
		drm.connector = drmModeGetConnector(drm.fd, drm.resources->connectors[i]);
		if (drm.connector->connection == DRM_MODE_CONNECTED)
            break; // Use it.
		drmModeFreeConnector(drm.connector);
		drm.connector = nullptr;
	}

    // Is DRM connected?
	if (!drm.connector) {
		// TODO: Listen for hotplug events and wait for a connector.
		syserror("No connected connector!");
		throw -1;
	}

	// Find preferred mode or the highest resolution mode.
	for (i = 0, area = 0; i < drm.connector->count_modes; i++) {
		drmModeModeInfo *current_mode = &drm.connector->modes[i];
		if (current_mode->type & DRM_MODE_TYPE_PREFERRED)
			drm.mode = current_mode;
		const auto current_area = current_mode->hdisplay * current_mode->vdisplay;
		if (current_area > area) {
			drm.mode = current_mode;
			area = current_area;
		}
	}

    // ??.
	if (!drm.mode) {
		syserror("Could not find DRM mode!");
        throw -1;
	}

	// Look for an encoder.
	for (i = 0; i < drm.resources->count_encoders; i++) {
		drm.encoder = drmModeGetEncoder(drm.fd, drm.resources->encoders[i]);
		if (drm.encoder->encoder_id == drm.connector->encoder_id)
			break;
		drmModeFreeEncoder(drm.encoder);
		drm.encoder = nullptr;
	}

    // If no encoder was found.
	if (drm.encoder)
		drm.crtc_id = drm.encoder->crtc_id;
    else {
    // Encoder was found.
		const auto crtc_id = find_crtc_for_connector(drm, drm.resources, drm.connector);
		if (crtc_id == 0) {
			syserror("No CRT controller found!");
			throw -1;
		}
		drm.crtc_id = crtc_id;
	}

    // ??.
	for (i = 0; i < drm.resources->count_crtcs; i++) {
		if (drm.resources->crtcs[i] == drm.crtc_id) {
			drm.crtc_index = i;
			break;
		}
	}

    // Cleanup.
	drmModeFreeResources(drm.resources);
}

// Deinitialize the direct rendering manager.
void drm::deinit() 
{
    if (close(fd) < 0)
        die("Failed to close the Direct Rendering Manager!");
}
