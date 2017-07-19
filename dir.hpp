#pragma once
#include "ent.hpp"

// Directory entry.
class dir : public ent {
public:
    dir();
    dir(const std::string& name);
    dir(const std::string& name, const entlist& files);
private:
    void init();
};
