#include <iostream>
#include "err.hpp"
#include "types.hpp"
#include "fb.hpp"
#include "col.hpp"
using namespace std;

ostream& operator<<(ostream& o, const err& e) {
    o << e.what();
    return o;
}

int main() {
    try {
        Fb fb;
        fb.fill(Rect(Pos(100, 100), Res(100, 100)), Col(255, 0, 0));
    } catch (const Err& e) {
        cerr << "Error code: " << hex << scast<int>(e) << endl;
    } catch (const err& e) {
        cerr << e << endl;
    }
    return 0;
}
