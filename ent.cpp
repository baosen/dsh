#include <cstring>
#include "log.hpp"
#include "ent.hpp"
using namespace std;

// Return codes:
#define SUCCESS 0 // Operation successful.

ent::ent() 
    : mode(0), nlink(0) 
{}

ent::ent(const mode_t mode)
    : mode(mode), nlink(0) 
{}

ent::ent(const mode_t mode, const nlink_t nlink)
    : mode(mode), nlink(nlink) 
{}

ent::ent(const std::string name, const mode_t mode)
    : name(name), mode(mode), nlink(0) 
{}

ent::ent(const std::string name, const mode_t mode, const entlist& files)
    : name(name), mode(mode), nlink(0), files(files)
{}

ent::ent(const std::string name, const mode_t mode, const nlink_t nlink)
    : name(name), mode(mode), nlink(nlink) 
{}

ent::ent(const std::string name, const mode_t mode, const nlink_t nlink, const entlist& files)
    : name(name), mode(mode), nlink(nlink), files(files) 
{}

// Is empty entry?
ent::operator bool() const
{
    return name.size() != 0;
}

// Is a directory?
bool ent::dir() const
{
    return (mode & S_IFDIR) == S_IFDIR;
}

// Is a file?
bool ent::file() const
{
    return (mode & S_IFREG) == S_IFREG;
}

// Open file.
int ent::open(const char *path) 
{
    warn("Bug: Trying to open an abstract entry!");
    return -EPERM;
}

// Create a new file entry.
void ent::push(const std::string name, const mode_t mode)
{
    files.push_back(make_shared<ent>(name, mode));
}

// Find entry pointed by s.
bool find(shared_ptr<ent>& e, const string& name)
{
    for (const auto& f : e->files) {
        if (name == f->name) {
            e = f;
            return true;
        }
    }
    return false;
}

shared_ptr<ent> ent::getent(const char* const path)
{
    const char     *s = path;
    shared_ptr<ent> e = make_shared<ent>(*this);

    // Is empty path?
    if (!strcmp(path, ""))
        return make_shared<ent>();

    // Is root directory?
    if (!strcmp(path, "/") && this->name == "/")
        return e;

    // Traverse path for the entry.
    do {
        if (*s == '/')
            ++s;

        stringstream ss;
        while (*s != '/' && *s != '\0') {
            ss << *s;
            ++s;
        }

        if (!find(e, ss.str()))
            return make_shared<ent>();
    } while (*s != '\0' && strcmp(s, "/"));

    // Found it!
    return e;
}

// Get directory entry if it exists.
shared_ptr<ent> ent::getdir(const char* const path)
{
    auto e = getent(path);
    if (!*e)
        return e;
    return e->dir() ? e : make_shared<ent>();
}

// Get file entry if it exists.
shared_ptr<ent> ent::getfile(const char* const path)
{
    auto e = getent(path);
    if (!*e)
        return e;
    return e->file() ? e : make_shared<ent>();
}

// Read from file to buffer.
int ent::read(char *buf, const off_t i, const size_t nbytes)
{
    UNUSED(buf);
    UNUSED(i);
    UNUSED(nbytes);
    return -EPERM; // Operation not permitted.
}

// Write to file.
int ent::write(const char *buf, const off_t i, const size_t nbytes)
{
    UNUSED(buf);
    UNUSED(i);
    UNUSED(nbytes);
    return -EPERM; // Operation not permitted.
}

// Output name of the file entry.
ostream& operator<<(ostream& o, const ent& e)
{
    o << e.name;
    return o;
}

// Output name of the file entry.
ostream& operator<<(ostream& o, const shared_ptr<ent>& e)
{
    o << e->name;
    return o;
}
