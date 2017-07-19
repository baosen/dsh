#pragma once
#include "ent.hpp"

class file : public ent {
public:
    file() 
        : ent(FILEMODE)
    {}

    file(const std::string& name) 
        : ent(name, FILEMODE)
    {}

    file(const std::string& name, const std::initializer_list<ent>& files)
        : ent(name, FILEMODE, 0, files) 
    {}
private:
    static const mode_t FILEMODE = S_IFREG | 0444;
};
