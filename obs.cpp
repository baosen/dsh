#include <list>
#include "keyboard.hpp"
using namespace std;

namespace {
    typedef void (*f)();
    list<f> keyboard_codes[MAX_KEYBOARD_CODES];
}

void handle(const int code, f f)
{
    keyboard_codes[code].push_back(f);
}
