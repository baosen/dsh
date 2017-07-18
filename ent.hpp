#pragma once
#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include <sys/stat.h>

// File entry.
struct ent {
    ent() {
    }

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

    operator bool() const
    {
        return name.size() != 0;
    }

    bool dir() const
    {
        return (mode & S_IFDIR) == S_IFDIR;
    }

    std::string    name;  // File name.
    mode_t         mode;  // Mode of file.
    nlink_t        nlink; // Number of hardlinks that points to this file that exists in the file system.
    std::list<ent> files; // If it is a directory, it can contain files.
};

// Find entry pointed by s.
inline ent find(const ent& e, const char **s)
{
    std::stringstream ss;
    
    if (**s == '\0')
        goto done;

    for (; **s != '/' && **s != '\0'; ++(*s))
        ss << **s;

    for (const auto& f : e.files)
        if (ss.str() == f.name)
            return f;

done: 
    return ent();
}

// Get directory entry if it exists.
template<ent& root>
inline ent getdirent(const char *path)
{
    const char *s = path;
    ent         e = root,
                found;

    do {
        e = find(e, &(++s));
        if (e)
            found = e;
    } while (*s != '\0' && e);

    return found.dir() ? found : ent();
}
