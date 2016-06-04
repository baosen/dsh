#include <list>
using namespace std;

namespace {
    typedef void (*f)();
    list<f> kb[10];
}

void handle(const int code, f f) {
    kb[code].push_back(f);
}
