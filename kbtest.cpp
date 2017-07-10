#include <iostream>
#include "err.hpp"
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

    for (;;) {
        cout << "key: " << kb.get() << endl;
    }
}
