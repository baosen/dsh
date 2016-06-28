#include <iostream>
#include "err.hpp"
#include "types.hpp"
using namespace std;

ostream& operator<<(ostream& o, const err& e) {
    o << e.what();
    return o;
}

int main() {
    try {
    } catch (const Err& e) {
        cerr << "Error code: " << hex << scast<int>(e) << endl;
    } catch (const err& e) {
        cerr << e << endl;
    }
    return 0;
}
