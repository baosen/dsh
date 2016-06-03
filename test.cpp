#include "kb.hpp"

int main() {
    openkb();
    for (;;)
        getkbcode();
}
