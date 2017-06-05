#pragma once

// Window system.
namespace wsys {
    // Initialize and setup window system.
    void init();
    // Write to window.
    void write(const char* name, const char *buf, const off_t i, const size_t size);
}
