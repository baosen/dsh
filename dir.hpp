#pragma once
#include "ent.hpp"

// Directory entry.
class dir : public ent {
public:
    dir();
    dir(const std::string& name);
    dir(const std::string& name, const entlist& files);

    // Open directory.
    virtual int open(const char *path) override;
private:
    void init();
};
