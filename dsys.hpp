#pragma once
#include <cstring>
#include "fb.hpp"

// Display system.
namespace dsys {
	// Initialize display system.
    void init();
	// Read from display.
    void read(const char* name, char *buf, const off_t i, const size_t size) noexcept;
	// Write to display.
    void write(const char* name, const char *buf, const off_t i, const size_t size) noexcept;
	// Deinitialize display system.
    void deinit();

	// Bit depths of color components.
	extern uint red,   // Bit depth of the red component.
		        green, // Bit depth of the green component.
		        blue,  // Bit depth of the blue component.
		        alpha; // Bit depth of the alpha component.
}
