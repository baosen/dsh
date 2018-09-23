#pragma once
#include <memory>
#include <string>
#include "pos.hpp"
#include "file.hpp"

class wndxc : public file {
public:
    wndxc(const std::string& pname);

    // Read from file.
    virtual int read(char *buf, const off_t i, const size_t nbytes) override;

    // Write to file.
    virtual int write(const char *buf, const off_t i, const size_t nbytes) override;
private:
    std::string pname;
};
