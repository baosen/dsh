#include <ft2build.h>
#include FT_FREETYPE_H
#include "framebuffer.hpp"
#include "log.hpp"
using namespace dshell;

class Ft {
public:
    Ft();
private:
    FT_Library l;
};

Ft::Ft() {
    const auto err = FT_Init_FreeType(&l);
    if (err)
        die("Failed to initialize Freetype!");
}

void draw(const Pos& p, const char *text) {
}
