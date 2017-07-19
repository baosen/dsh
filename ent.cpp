#include <cstring>
#include "ent.hpp"
using namespace std;

// Return codes:
#define SUCCESS 0 // Operation successful.

ent::ent() {}

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

void ent::push(const std::string name, const mode_t mode)
{
    files.push_back(make_unique<ent>(name, mode));
}

// Find entry pointed by s.
shared_ptr<ent> find(const shared_ptr<ent>& e, const char **s)
{
    std::stringstream ss;
    
    if (**s == '\0')
        goto done;

    for (; **s != '/' && **s != '\0'; ++(*s))
        ss << **s;

    for (const auto& f : e->files)
        if (ss.str() == f->name)
            return f;

done: 
    return make_shared<ent>();
}

// Get directory entry if it exists.
shared_ptr<ent> ent::getdir(const char* const path)
{
    const char     *s = path;
    shared_ptr<ent> e = make_shared<ent>(*this), 
                    found;

    // Is root directory?
    if (!strcmp(path, "/") && this->name == "/")
        return e;

    // Traverse file tree.
    do {
        e = find(e, &(++s));
        if (*e)
            found = e;
    } while (*s != '\0' && *e);

    return found->dir() ? found : make_shared<ent>();
}

// Get file entry if it exists.
shared_ptr<ent> ent::getfile(const char* const path)
{
    const char     *s = path;
    shared_ptr<ent> e = make_shared<ent>(*this), 
                    found;

    if (!strcmp(path, "/"))
        return make_shared<ent>();

    if (path[0] == '/')
        ++s;

    do {
        e = find(e, &s);
        if (*e)
            found = e;
    } while (*s != '\0' && *e);

    return found->file() ? found : make_shared<ent>();
}

// Get entry if it exists.
shared_ptr<ent> ent::getent(const char* const path)
{
    const char     *s = path;
    shared_ptr<ent> e = make_shared<ent>(*this), 
                    found;

    if (!strcmp(path, "/") && this->name == "/")
        return e;

    if (path[0] == '/')
        ++s;

    do {
        e = find(e, &s);
        if (*e)
            found = e;
    } while (*s != '\0' && *e);

    return found;
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
