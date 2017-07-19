#pragma once
#include "ent.hpp"

// Directory entry.
class dir : public ent {
public:
    dir();
    dir(const std::string& name);
    dir(const std::string& name, const std::initializer_list<ent>& files);
private:
    void init();
};
