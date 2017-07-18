#include <iostream>
#include "m.hpp"
using namespace std;

// Mouse tests.
int main() 
{
    // Test "hacky" mouse.
    m m(1); // Open mouse1.
    forever {
        const auto e = m.rd();
        cout << "x: " << e.x << " y: " << e.y << " left: " << e.left << " mid: " << e.mid << " right: " << e.right << endl;
    }
    return 0;
}
