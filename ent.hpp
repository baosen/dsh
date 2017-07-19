#pragma once
#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include <sys/stat.h>
#include "types.hpp"
#include "fs.hpp"

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

    // TODO: Implement move constructor and replace push_back with emplace_back.

    // Is empty entry?
    operator bool() const;

    // Is a directory?
    bool dir() const;
    // Is a file?
    bool file() const;

    // Get directory entry if it exists.
    ent getdir(const char* const path);

    // Get file entry if it exists.
    ent getfile(const char* const path);

    // Get entry if it exists.
    ent getent(const char* const path);

    // Read from file.
    virtual int read(char *buf, const off_t i, const size_t nbytes);

    // Write to file.
    virtual int write(const char *buf, const off_t i, const size_t nbytes);

protected:
    void push(const std::string name, const mode_t mode);

private:
    std::string    name;  // File name.
    mode_t         mode;  // Mode of file.
    nlink_t        nlink; // Number of hardlinks that points to this file that exists in the file system.
    std::list<ent> files; // If it is a directory, it can contain files.

    friend ent find(const ent& e, const char **s);
    friend int fs::getattr(const  char  *path, struct stat  *stbuf);
    friend int fs::readdir(const char *path, void *buf, fuse_fill_dir_t fill, off_t offset, struct fuse_file_info *fi);    
    
    // Output name of the file entry.
    friend std::ostream& operator<<(std::ostream& o, const ent& e);
};
