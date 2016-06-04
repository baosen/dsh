#include <list>
#include "kb.hpp"
using namespace std;

namespace {
    typedef void (*f)();
    list<f> kb[NCODES];
}

void handle(const int code, f f) {
    kb[code].push_back(f);
}
