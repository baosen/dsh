#include "file.hpp"

static const mode_t FILEMODE = S_IFREG | 0444;

file::file() 
    : ent(FILEMODE)
{}

file::file(const std::string& name) 
    : ent(name, FILEMODE)
{}

file::file(const std::string& name, const entlist& files)
    : ent(name, FILEMODE, files) 
{}