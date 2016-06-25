#include "kb.hpp"

int main()
{
    openkb();

    for (;;) {
        getkbcode();
    }

    return EXIT_SUCCESS;
}
