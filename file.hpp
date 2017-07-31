#pragma once
#include "ent.hpp"

class file : public ent {
public:
    // Create an empty file.
    file();
    // Create an file with a name.
    file(const std::string& name);
    // Create an file with a name and initialize it with files.
    file(const std::string& name, const entlist& files);

    // Open file.
    virtual int open(const char *path) override;
};
