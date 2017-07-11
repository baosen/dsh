#include <cstdio>
#include "err.hpp"
#include "kbc.hpp"
#include "kb.hpp"
using namespace std;

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

    kb.open();
/*
    for (;;)
        kb.get();
*/

    wchar_t c[2] = {0};
    for (;;) {
        c[0] = towc(kb.rd());
        if (c[0] == '\0')
            continue;
        printf("%ls\n", c);
    }
}
