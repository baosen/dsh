#pragma once
#include "file.hpp"

class wndy : public file {
public:
    wndy();

    virtual int read(char        *buf, const off_t i, const size_t nbytes);
    virtual int write(const char *buf, const off_t i, const size_t nbytes);
private:
    uint y;
};
