#pragma once
#include "fio.hpp"

// Window system.
namespace wsys {
    // Initialize and setup window system.
    void init();

    // Deinitialize the window system.
    void deinit();

    // Read from window.
    int  read(const char* name, void *buf, const off_t i, const size_t size);

    // Write to window.
    void write(const char* name, const void *buf, const off_t i, const size_t size);
}
