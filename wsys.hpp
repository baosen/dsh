#pragma once
#include "fio.hpp"

// Window system.
namespace wsys {
    // Initialize and setup window system.
    void init();

    // Deinitialize the window system.
    void deinit();

    // Read from window.
    int  read(const char  *name,  // File name.
              void        *buf,   // Buffer to read to.
              const off_t  i,     // Offset.
              const size_t size); // Size/length of read in bytes.

    // Write to window.
    void write(const char  *name,  // File name.
               const void  *buf,   // Buffer to write from.
               const off_t  i,     // Offset.
               const size_t size); // Size/length of write in bytes.
}
