#include <iostream>
#include "err.hpp"
using namespace std;

ostream& operator<<(ostream& o, const err& e) {
    o << e.what();
    return o;
}

int main() {
    try {
    } catch (const err& e) {
        cerr << e;
    }
    return 0;
}
