#pragma once
#include "file.hpp"

// Keyboard file.
class kbf : public file {
public:
    kbf(const std::string name);

    // Read linux keyboard input events.
    virtual int read(char *buf, const off_t i, const size_t nbytes);

    // Keyboard is read-only.
    virtual int write(const char *buf, const off_t i, const size_t nbytes);
};
