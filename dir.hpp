#pragma once

// Directory entry.
struct dir : ent {
    dir() 
        : ent(S_IFDIR | 0755, 0)
    {}

    dir(const std::string name, const std::initializer_list<ent>& files)
        : ent(name, S_IFDIR | 0755, 0, files) 
    {}
};
