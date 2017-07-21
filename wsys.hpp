#pragma once
#include <list>
#include <unordered_map>
#include <string>
#include <memory>
#include "fio.hpp"
#include "wnd.hpp"

// Window system.
namespace wsys {
    // Initialize and setup window system.
    void init();

    // Deinitialize the window system.
    void deinit();

    uint getx(const char *name);
    uint gety(const char *name);

    void move(const char *name, const pos& p);
    void movex(const char *name, const uint x);
    void movey(const char *name, const uint y);

    // Read from window.
    int  read(const char  *name,  // File name.
              void        *buf,   // Buffer to read to.
              const off_t  i,     // Offset.
              const size_t size); // Size/length of read in bytes.

    // Write to window.
    int  write(const char  *name,  // File name.
               const char  *buf,   // Buffer to write from.
               const off_t  i,     // Offset.
               const size_t size); // Size/length of write in bytes.
}
