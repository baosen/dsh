#pragma once
#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include <memory>
#include <sys/stat.h>
#include "types.hpp"
#include "fs.hpp"

class ent;
class wndctl;
typedef std::initializer_list<std::shared_ptr<ent>> entlist;

// File entry.
class ent {
public:
    ent();
    ent(const mode_t mode);
    ent(const mode_t mode, const nlink_t nlink);
    ent(const std::string name, const mode_t mode);
    ent(const std::string name, const mode_t mode, const entlist& files);
    ent(const std::string name, const mode_t mode, const nlink_t nlink);
    ent(const std::string name, const mode_t mode, const nlink_t nlink, const entlist& files);

    // Is empty entry?
    operator bool() const;

    // Is a directory?
    bool dir() const;
    // Is a file?
    bool file() const;

    // Get entry if it exists.
    std::shared_ptr<ent> getent(const char* const path);

    // Get directory entry if it exists.
    std::shared_ptr<ent> getdir(const char* const path);

    // Get file entry if it exists.
    std::shared_ptr<ent> getfile(const char* const path);

    // Read from file.
    virtual int read(char *buf, const off_t i, const size_t nbytes);

    // Write to file.
    virtual int write(const char *buf, const off_t i, const size_t nbytes);

    // Open file.
    virtual int open(const char *path);

    // Control window.
    virtual int ioctl(int   cmd,   // The ioctl() command number passed.
                      void *data); // The data.

    virtual ~ent() {}
protected:
    void push(const std::string name, const mode_t mode);

    std::string                     name;  // File name.
private:
    mode_t                          mode;  // Mode of file.
    nlink_t                         nlink; // Number of hardlinks that points to this file that exists in the file system.
    std::list<std::shared_ptr<ent>> files; // If it is a directory, it can contain files.

    friend bool find(std::shared_ptr<ent>& e, const std::string& name);

    // Friends of the file system.
    friend int  fs::getattr(const char *path, struct stat *stbuf);
    friend int  fs::readdir(const char *path, void *buf, fuse_fill_dir_t fill, off_t offset, struct fuse_file_info *fi);    
    
    // Output name of the file entry.
    friend std::ostream& operator<<(std::ostream& o, const ent& e);
    // Output name of the file entry.
    friend std::ostream& operator<<(std::ostream& o, const std::shared_ptr<ent>& e);

    // Control window.
    friend class wndctl;
};
