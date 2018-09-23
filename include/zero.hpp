#pragma once
#include <cstring>

// Zero out the memory to the object.
template<class T>
void zero(T& o) {
    ::memset(&o, 0, sizeof o);
}
