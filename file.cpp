#include "file.hpp"
#include "errno.hpp"

static const mode_t FILEMODE = S_IFREG | 0444;

// Create an empty file.
file::file() 
    : ent(FILEMODE)
{}

// Create an file with a name.
file::file(const std::string& name) 
    : ent(name, FILEMODE)
{}

// Create an file with a name and initialize it with files.
file::file(const std::string& name, const entlist& files)
    : ent(name, FILEMODE, files) 
{}

// Open file.
int file::open(const char *path)
{
    UNUSED(path);

    return SUCCESS;
}
