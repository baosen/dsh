#include "config.hpp"
#include <xf86drm.h>
#include <xf86drmMode.h>
#include "types.hpp"
#include "log.hpp"
#include "zero.hpp"
#include "fio.hpp"
#include "drm.hpp"

// Direct Rendering Manager-system.
namespace {
    int fd = -1; // The file descriptor to DRM device.

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
    Drm d;
    zero(d);
    int i,    // index.
        area; // ??.

    // Open DRM device file.
    if ((d.fd = ::open(CARD0_PATH, O_RDWR)) < 0)
        // TODO: Warn about this error here.
        throw errno; 

    // Get DRM mode resources.
	if (!(d.resources = drmModeGetResources(d.fd))) {
        syserror("Failed to get DRM mode resources!");
        throw -1;
    }

	// Find a connected connector.
	for (i = 0; i < d.resources->count_connectors; i++) {
        // Is connector connected?
		d.connector = drmModeGetConnector(d.fd, d.resources->connectors[i]);
		if (d.connector->connection == DRM_MODE_CONNECTED)
            break; // Use it.
		drmModeFreeConnector(d.connector);
		d.connector = nullptr;
	}

    // Is DRM connected?
	if (!d.connector) {
		// TODO: Listen for hotplug events and wait for a connector.
		syserror("No connected connector!");
		throw -1;
	}

	// Find preferred resolution mode or use the highest resolution mode.
	for (i = 0, area = 0; i < d.connector->count_modes; i++) {
        // Current mode.
		drmModeModeInfo *cmode = &d.connector->modes[i];

        // Found mode preferred by the device.
		if (cmode->type & DRM_MODE_TYPE_PREFERRED)
			d.mode = cmode;

        // Resolution for the current mode.
		const auto carea = cmode->hdisplay * cmode->vdisplay;
        // If it is larger, use the area.
		if (carea > area) {
			d.mode = cmode;
			area     = carea;
		}
	}

    // Check if we found a usable DRM mode.
	if (!d.mode) {
		syserror("Could not find any useable DRM mode!");
        throw -1;
	}

	// Look for an encoder. (wtf is this???)
	for (i = 0; i < d.resources->count_encoders; i++) {
		d.encoder = drmModeGetEncoder(d.fd, d.resources->encoders[i]);

		if (d.encoder->encoder_id == d.connector->encoder_id)
			break;

		drmModeFreeEncoder(d.encoder);
		d.encoder = nullptr;
	}

    // If no encoder was found.
	if (d.encoder)
		d.crtc_id = d.encoder->crtc_id;
    else { // Encoder was found.
		const auto id = find_crtc_for_connector(d, d.resources, d.connector);
		if (id == 0) {
			syserror("No CRT controller found!");
			throw -1;
		}
		d.crtc_id = id;
	}

    // Iterate over CRT controllers?
	for (i = 0; i < d.resources->count_crtcs; i++) {
		if (d.resources->crtcs[i] == d.crtc_id) {
			d.crtc_index = i;
			break;
		}
	}

    // Cleanup.
	drmModeFreeResources(d.resources);
}

// Deinitialize the direct rendering manager.
void drm::deinit() 
{
    if (close(fd) < 0)
        die("Failed to close the Direct Rendering Manager file!");
}
