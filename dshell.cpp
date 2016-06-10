#include "ft.hpp"
#include "fb.hpp"
#include "kb.hpp"
#include "taskb.hpp"

class Panel {
public:
// TODO: Drag.
};

// Different ways for windows to be laid out.
class Layout {
protected:
    void place();
};

enum {
    NOT_FOUND
};

#define forever for (;;)

namespace {
    void setup() {
        init_ft();
        init_framebuffer();
        make_taskb();
    }
    
    void destroy_shell() {
        destroy_taskb();
        destroy_framebuffer();
    }

    void run() {
        forever {
            auto kbcode = get_keyboard_code();
            switch (kbcode) {
            }
        }
    }
}

int main() {
    try {
        setup();
        run();
        destroy_shell();
    } catch(...) {
        destroy_shell();
        throw;
    }
    return 0;
}
