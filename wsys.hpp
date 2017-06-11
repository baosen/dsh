#pragma once

// Window system.
namespace wsys {
    // Initialize and setup window system.
    void init();
    // Deinitialize the window system.
    void deinit();
    // Read from window.
    void read(const char* name, const char *buf, const off_t i, const size_t size);
    // Write to window.
    void write(const char* name, const char *buf, const off_t i, const size_t size);
}
