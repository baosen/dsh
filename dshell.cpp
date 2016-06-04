#include "ft.hpp"
#include "fb.hpp"
#include "kb.hpp"
#include "taskb.hpp"

class Pan {
public:
// TODO: Drag.
};

// Different ways for windows to be laid out.
class Lay {
protected:
    void place();
};

class Float : Lay {
};

class Tiled : Lay {
};

enum {
    NOT_FOUND
};

void h1() {
}

namespace {
    void setup() {
        init_ft();
        init_fb();
        make_taskb();
    }
    
    void destroy() {
        destroy_taskb();
        destroy_fb();
    }

    void run() {
        for (;;) {
            auto code = getkbcode();
        }
    }
}

int main() {
    try {
        setup();
        run();
        destroy();
    } catch(...) {
        destroy();
        throw;
    }
    return 0;
}
