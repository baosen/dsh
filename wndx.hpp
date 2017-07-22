#pragma once
#include <memory>
#include "pos.hpp"
#include "file.hpp"

class wndx : public file {
public:
    wndx();
    wndx(const std::shared_ptr<class dir>& parent);

    virtual int read(const  char *path, char *buf, const off_t i, const size_t nbytes);
    virtual int write(const char *path, const char *buf, const off_t i, const size_t nbytes);
private:
    std::shared_ptr<class dir> parent;
};
