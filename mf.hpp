#pragma once

// Mouse file.
class mf : ent {
public:
    virtual int read(const char *buf, const off_t i, const size_t nbytes)
    {
    }

    virtual int write(char *buf, const off_t i, const size_t nbytes)
    {
    }
};
