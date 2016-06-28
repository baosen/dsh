#pragma once
#include "types.hpp"
#include "pos.hpp"
#include "rect.hpp"

class Fb {
public:
    Fb();
    void fill(const Rect& r, const int c);
    char& operator()(const Pos&);
    ~Fb();
};
