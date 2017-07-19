#pragma once
#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include <sys/stat.h>
#include "types.hpp"

// File entry.
class ent {
public:
    ent();
    ent(const mode_t mode);
    ent(const mode_t mode, const nlink_t nlink);
    ent(const std::string name, const mode_t mode);
    ent(const std::string name, const mode_t mode, const std::initializer_list<ent>& files);
    ent(const std::string name, const mode_t mode, const nlink_t nlink);
    ent(const std::string name, const mode_t mode, const nlink_t nlink, const std::initializer_list<ent>& files);

    // Is empty entry?
    operator bool() const;

    // Is a directory?
    bool dir() const;

    // Get directory entry if it exists.
    ent getdir(const char* const path);

    // Read from file.
    virtual int read(const char *buf, const off_t i, const size_t nbytes);

    // Write to file.
    virtual int write(char *buf, const off_t i, const size_t nbytes);
private:
    std::string    name;  // File name.
    mode_t         mode;  // Mode of file.
    nlink_t        nlink; // Number of hardlinks that points to this file that exists in the file system.
    std::list<ent> files; // If it is a directory, it can contain files.

    friend ent find(const ent& e, const char **s);
    
    // Output name of the file entry.
    friend std::ostream& operator<<(std::ostream& o, const ent& e);
};
