#pragma once
#include "pos.hpp"
#include "file.hpp"

class wndx : public file {
public:
    wndx();

    virtual int read(char        *buf, const off_t i, const size_t nbytes);
    virtual int write(const char *buf, const off_t i, const size_t nbytes);
private:
    uint x;
};
