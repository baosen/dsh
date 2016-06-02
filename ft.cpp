#include <ft2build.h>
#include FT_FREETYPE_H
#include "log.hpp"
using namespace dshell;

namespace {
    FT_Library lib;
    
    void init_ft() {
        auto err = FT_Init_FreeType(&lib);
        if (err)
            die("Failed to initialize Freetype!");
    }
}
