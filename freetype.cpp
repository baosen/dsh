#include <ft2build.h>
#include FT_FREETYPE_H
#include "framebuffer.hpp"
#include "log.hpp"
using namespace dshell;

namespace {
    FT_Library lib;
    
    void init_freetype() {
        auto err = FT_Init_FreeType(&lib);
        if (err)
            die("Failed to initialize Freetype!");
    }
}

void draw(const uint x, const uint y, const char *text) {
}
