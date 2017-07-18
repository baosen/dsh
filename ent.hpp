#pragma once
#include <string>
#include <list>
#include <sys/stat.h>

// File entry.
class ent {
public:
    ent(const std::string name, const mode_t mode)
        : name(name), mode(mode), nlink(0) 
    {}

    ent(const std::string name, const mode_t mode, const std::initializer_list<ent> files)
        : name(name), mode(mode), nlink(0), files(files) 
    {}

    ent(const std::string name, const mode_t mode, const nlink_t nlink)
        : name(name), mode(mode), nlink(nlink) 
    {}

    ent(const std::string name, const mode_t mode, const nlink_t nlink, const std::initializer_list<ent> files)
        : name(name), mode(mode), nlink(nlink), files(files) 
    {}
private:
    std::string    name;  // File name.
    mode_t         mode;  // Mode of file.
    nlink_t        nlink; // Number of hardlinks that points to this file that exists in the file system.
    std::list<ent> files; // If it is a directory, it can contain files.
};

