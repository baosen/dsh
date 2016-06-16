#include "freetype.hpp"
#include "framebuffer.hpp"
#include "singleton.h"
#include "keyboard.hpp"

class Panel {
public:
// TODO: Drag.
};

// Different ways for windows to be laid out.
class Layout {
protected:
    void place();
};

namespace {
    void setup_dshell() {
        init_freetype();
        setup_framebuffer();
    }
    
    void destroy_dshell() {
        destroy_framebuffer();
    }

    void run_dshell() {
        forever {
            auto kbcode = get_keyboard_code();
            switch (kbcode) {
            }
        }
    }
}

int main()
{
    auto framebuffer = Singleton<Framebuffer>::get_instance();

    try {
        setup_dshell();
        run_dshell();
        destroy_dshell();
    } catch(...) {
        destroy_dshell();
        throw;
    }

    return EXIT_SUCCESS;
}
