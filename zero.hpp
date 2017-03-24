#pragma once
#include <cstring>

template<class T>
void zero(T& o) {
    ::memset(&o, 0, sizeof o);
}