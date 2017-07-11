#include <cstdio>
#include "err.hpp"
#include "kbc.hpp"
#include "kb.hpp"
using namespace std;

static void wctest(Kb& kb)
{
    wchar_t     c[2] = {0};
    input_event k;
    for (;;) {
        k    = kb.rd();
        c[0] = towc(k);
        if (c[0] == '\0')
            continue;
        printf("code: %02x\n", k.code);
        printf("char: %ls\n", c);
    }
}

static void asciitest(Kb& kb)
{
    char c;
    input_event k;
    for (;;) {
        k = kb.rd();
        c = toc(k);
        if (c == '\0')
            continue;
        printf("code: %02x\n", k.code);
        printf("char: %c\n", c);
    }
}

static void dbgtest(Kb& kb)
{
    kb.open();
    for (;;)
        kb.get();
}

int main()
{
    Kb kb;

    try {
        kb.get();
        cerr << "Failed to catch keyboard exception!" << endl;
        return EXIT_FAILURE;
    } catch (const err& e) {
        cout << "Succeeded catching keyboard exception!" << endl;
    }

    dbgtest(kb);
}
