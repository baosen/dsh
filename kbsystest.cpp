#include <cstdio>
#include "kbsys.hpp"
#include "kbc.hpp"
using namespace std;
using namespace kbsys;

// Setup keyboard subsystem twice to test deinitialization.
static void resetup()
{
    init();
    deinit();
    init();
}

// Test keyboard subsystem.
int main()
{
    resetup();

    input_event e;
    char        c;
    for (;;) {
        e = get();
        c = toc(e);
        if (c == '\0')
            continue;
        printf("code: %02x\n", e.code);
        printf("char: %c\n", c);
    }

    deinit();
    return EXIT_SUCCESS;
}
