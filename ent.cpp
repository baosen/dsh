#include "ent.hpp"

ent::ent() {}

ent::ent(const mode_t mode, const nlink_t nlink)
    : mode(mode), nlink(nlink) 
{}

ent::ent(const std::string name, const mode_t mode)
    : name(name), mode(mode), nlink(0) 
{}

ent::ent(const std::string name, const mode_t mode, const std::initializer_list<ent>& files)
    : name(name), mode(mode), nlink(0), files(files) 
{}

ent::ent(const std::string name, const mode_t mode, const nlink_t nlink)
    : name(name), mode(mode), nlink(nlink) 
{}

ent::ent(const std::string name, const mode_t mode, const nlink_t nlink, const std::initializer_list<ent>& files)
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

// Get directory entry if it exists.
ent ent::getdirent(const char *path)
{
    const char *s = path;
    ent         e = *this,
                found;

    do {
        e = find(e, &(++s));
        if (e)
            found = e;
    } while (*s != '\0' && e);

    return found.dir() ? found : ent();
}

// Read from file.
int ent::read(char *buf, const off_t i, const size_t nbytes)
{
    UNUSED(buf);
    UNUSED(i);
    UNUSED(nbytes);
    return -EPERM; // Operation not permitted.
}

// Write to file.
int ent::write(char *buf, const off_t i, const size_t nbytes)
{
    UNUSED(buf);
    UNUSED(i);
    UNUSED(nbytes);
    return -EPERM; // Operation not permitted.
}

// Find entry pointed by s.
ent find(const ent& e, const char **s)
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
