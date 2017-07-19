#pragma once
#include "ent.hpp"

// Mouse file.
class mf : public ent {
public:
    virtual int read(char *buf, const off_t i, const size_t nbytes);
    virtual int write(const char *buf, const off_t i, const size_t nbytes);
};
