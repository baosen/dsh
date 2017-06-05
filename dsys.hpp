#pragma once
#include <cstring>
#include "fb.hpp"

// Display system.
namespace dsys {
    void init();
    void copy(const char *buf, const off_t i, const size_t size);
    void read(const char* name, const char *buf, const off_t i, const size_t size);
    void deinit();
}
