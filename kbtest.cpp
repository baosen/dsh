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
        k    = kb.rd1();
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
        k = kb.rd1();
        cout << "Read!" << endl;
        c = toc(k);
        if (c == '\0')
            continue;
        printf("code: %02x\n", k.code);
        printf("char: %c\n", c);
    }
}

static void get1(Kb& kb)
{
    for (;;)
        kb.get1();
}

static void get2(Kb& kb)
{
    for (;;)
        kb.get2();
}

int main()
{
    Kb kb;

    try {
        kb.rd1();
        cerr << "Failed to catch keyboard exception!" << endl;
        return EXIT_FAILURE;
    } catch (const err& e) {
        cout << "Succeeded catching keyboard exception!" << endl;
    }

    try {
        kb.rd2();
        cerr << "Failed to catch keyboard exception!" << endl;
        return EXIT_FAILURE;
    } catch (const err& e) {
        cout << "Succeeded catching keyboard exception!" << endl;
    }

    kb.open();

    //get1(kb);
    //asciitest(kb);
    wctest(kb);
}
