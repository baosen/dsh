#include "types.hpp"

namespace dshell {
    void init_fb();
    char& access(const uint x, const uint y);
    uint maxw();
    uint maxh();
    void destroy_fb();
}
