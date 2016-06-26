#pragma once
#include "types.hpp"
#include "pos.hpp"

class Fb {
public:
    Fb();
    char& operator()(const Pos&);
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
