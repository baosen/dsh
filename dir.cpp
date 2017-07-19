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

dir::dir(const std::string& name, const std::initializer_list<ent>& files)
    : ent(name, DIRMODE, 0, files) 
{    
    init();
}

void dir::init()
{
    push(".", DIRMODE);  // "This" directory.
    push("..", DIRMODE); // Parent directory.
}
