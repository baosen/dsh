#pragma once
#include <string>
#include "file.hpp"

class wndy : public file {
public:
    wndy(const std::string& pname);

    // Read from file.
    virtual int read(char *buf, const off_t i, const size_t nbytes) override;

    // Write to file.
    virtual int write(const char *buf, const off_t i, const size_t nbytes) override;
private:
    std::string pname;
};
