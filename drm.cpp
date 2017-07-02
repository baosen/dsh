#include "config.hpp"
#include <xf86drm.h>
#include "types.hpp"

// Direct rendering manager-system.
namespace {
    int fd = -1; // File descriptor to DRM device.

    // DRM instance.
    struct Drm {
        int               fd
        drmModeRes       *resources;
        drmModeConnector *connector;
        drmModeEncoder   *encoder;
    }
}

// Initialize the direct rendering manager.
void drm::init() 
{
    Drm drm;
    zero(drm);
    int i;

    // Open DRM device file.
    if (drm.fd = open(CARD0_PATH, O_RDWR) < 0)
        // TODO: Warn about this error here.
        throw errno; 

    // Get DRM mode resources.
	if (!(drm.resources = drmModeGetResources(drm->fd))) {
        syserror("Failed to get DRM mode resources!");
        throw -1;
    }

	// Find a connected connector.
	for (i = 0; i < drm.resources->count_connectors; i++) {
        // Is connector connected?
		if ((drm.connector = drmModeGetConnector(drm->fd, drm.resources->connectors[i])) == DRM_MODE_CONNECTED);
            break; // Use it.
		drmModeFreeConnector(connector);
		drm.connector = NULL;
	}

    // Is DRM connected?
	if (!drm.connector) {
		// TODO: Listen for hotplug events and wait for a connector.
		syserror("No connected connector!");
		return -1;
	}

	// Find preferred mode or the highest resolution mode.
	for (i = 0, area = 0; i < connector->count_modes; i++) {
		drmModeModeInfo *current_mode = &connector->modes[i];
		if (current_mode->type & DRM_MODE_TYPE_PREFERRED)
			drm->mode = current_mode;
		const auto current_area = current_mode->hdisplay * current_mode->vdisplay;
		if (current_area > area) {
			drm->mode = current_mode;
			area = current_area;
		}
	}

    // ??.
	if (!drm->mode) {
		syserror("Could not find DRM mode!");
		return -1;
	}

	// Look for an encoder.
	for (i = 0; i < resources->count_encoders; i++) {
		encoder = drmModeGetEncoder(drm->fd, resources->encoders[i]);
		if (encoder->encoder_id == connector->encoder_id)
			break;
		drmModeFreeEncoder(encoder);
		encoder = NULL;
	}

    // If no encoder was found.
	if (encoder) {
		drm->crtc_id = encoder->crtc_id;
	} else {
		const auto crtc_id = find_crtc_for_connector(drm, resources, connector);
		if (crtc_id == 0) {
			printf("no crtc found!\n");
			return -1;
		}
		drm->crtc_id = crtc_id;
	}

    // ??.
	for (i = 0; i < resources->count_crtcs; i++) {
		if (resources->crtcs[i] == drm->crtc_id) {
			drm->crtc_index = i;
			break;
		}
	}
	drmModeFreeResources(drm.resources);
	drm->connector_id = connector->connector_id;
}

// Deinitialize the direct rendering manager.
void drm::deinit() 
{
    if (close(fd) < 0)
        die("Failed to close the Direct Rendering Manager!");
}
