#pragma once

class Fb {
public:
    Fb();
    char& operator()(const unsigned int x, const unsigned int y);
    ~Fb();
private:
    auto vinfo();
    auto finfo();
    char* map();
    void open();
    void setup();

    int fbfd;
    unsigned int width, height;
    char*  fb;
    size_t size;
};
