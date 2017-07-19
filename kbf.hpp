#pragma once
#include "ent.hpp"

// Keyboard file.
class kbf : public ent {
public:
    // Read linux keyboard input events.
    virtual int read(char *buf, const off_t i, const size_t nbytes);

    // Keyboard is read-only.
    virtual int write(const char *buf, const off_t i, const size_t nbytes);
};
