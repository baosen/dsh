#include <iostream>
#include "evm.hpp"
using namespace std;

// Event mouse file tests.
// Check to see if the event mouse works.
int main()
{
    Evm m(0);

    forever {
        const auto e = m.rd();
        cout << "type: " << e.type << " code: " << e.code << " value: " << e.value << endl;
    }

    return EXIT_SUCCESS;
}
