#include <cstdio>
#include <iostream>
#include <cwchar>
#include "kbsys.hpp"
#include "kbc.hpp"
#include "locale.hpp"
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
    wchar_t     c;
    input_event e;
    for (;;) {
        e = get();
        c = towc(e);
        if (c == '\0') {
            //wcout << L"code: " << hex << e.code << dec << endl;
            continue;
        }
        //printf("code: %02x\n", e.code);
        //printf("char: %ls\n", c);
        wcout << L"code: " << hex << e.code << dec << L'\n'
              << L"char: " << c << endl;
    }
}

// Test keyboard subsystem.
int main()
{
    resetup();
    setwc();

    wctest();

    deinit();
    return EXIT_SUCCESS;
}
