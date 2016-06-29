#include "kb.hpp"
#include "types.hpp"

int main() {
    Kb kb;
    forever {
        kb.getkbcode();
    }
    return 0;
}
