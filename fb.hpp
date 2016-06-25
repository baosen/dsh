#pragma once
#include "types.hpp"

class Fb {
public:
    Fb();
    char& operator()(const uint x, const uint y);
    ~Fb();
private:
    auto vinfo();
    auto finfo();
    char* map();
    void open();
    void setup();

    int fd;
    uint w, h;
    char*  fb;
    size_t size;
};
