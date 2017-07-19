#pragma once
#include "ent.hpp"

class file : public ent {
public:
    file();
    file(const std::string& name);
    file(const std::string& name, const entlist& files);
};
