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

static void asciitest()
{
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
}

static void wctest()
{
    wchar_t     c[2] = {0};
    input_event e;
    for (;;) {
        e    = get();
        c[0] = towc(e);
        if (c[0] == '\0')
            continue;
        printf("code: %02x\n", e.code);
        printf("char: %ls\n", c);
    }
}

// Test keyboard subsystem.
int main()
{
    resetup();

    wctest();

    deinit();
    return EXIT_SUCCESS;
}
