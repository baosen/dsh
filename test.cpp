#include "mouse.hpp"
#include "types.hpp"

int main() {
    Mouse m;
    forever {
        m.read();
    }
    return 0;
}
