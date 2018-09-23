#pragma once
#include "file.hpp"

// Mouse file.
class mf : public file {
public:
    mf(const std::string name);

    virtual int read(char *buf, const off_t i, const size_t nbytes);
    virtual int write(const char *buf, const off_t i, const size_t nbytes);
};
