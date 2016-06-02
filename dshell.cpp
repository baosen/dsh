#include "ft.hpp"
#include "fb.hpp"
#include "taskb.hpp"

namespace dshell {
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
}
using namespace dshell;

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
}

int main() {
    try {
        setup();
    } catch(...) {
        destroy();
        throw;
    }
    return 0;
}
