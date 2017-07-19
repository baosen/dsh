#include "dir.hpp"

static const mode_t DIRMODE = S_IFDIR | 0755;

dir::dir() 
    : ent(DIRMODE)
{
    init();
}

dir::dir(const std::string& name) 
    : ent(name, DIRMODE)
{    
   init(); 
}

dir::dir(const std::string& name, const entlist& files)
    : ent(name, DIRMODE, files) 
{    
    init();
}

void dir::init()
{
    push(".", DIRMODE);  // "This" directory.
    push("..", DIRMODE); // Parent directory.
}
