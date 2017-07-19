#pragma once
#include "ent.hpp"

// Directory entry.
class dir : public ent {
public:
    dir() 
        : ent(DIRMODE)
    {}

    dir(const std::string& name) 
        : ent(name, DIRMODE)
    {}

    dir(const std::string& name, const std::initializer_list<ent>& files)
        : ent(name, DIRMODE, 0, files) 
    {}
private:
    static const mode_t DIRMODE = S_IFDIR | 0755;
};
