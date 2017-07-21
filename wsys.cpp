#include "wsys.hpp"
using namespace std;

// Windows managed by the windowing subsystem.
static unordered_map<string, unique_ptr<wnd>> wnds;

// Initialize and setup window system.
void wsys::init() 
{}

// Deinitialize the window system.
void wsys::deinit() 
{
    wnds.clear();
}

// Check if window exist. If it exists, get it!
auto& get(const char *name)
{
    auto it = wnds.find(name);
    if (it == wnds.end()) 
        throw err("No window named " + string(name) + " found!");
    return it->second;
}

uint wsys::getx(const char *name)
{
    return get(name)->pcur.x;
}

uint wsys::gety(const char *name)
{
    return get(name)->pcur.y;
}

void wsys::move(const char *name, const pos& p)
{
    get(name)->move(p);
}

void wsys::movex(const char *name, const uint x)
{
    get(name)->movex(x);
}

void wsys::movey(const char *name, const uint y)
{
    get(name)->movey(y);
}

// Read from window.
int wsys::read(const char  *name, // Name of the window.
               void        *buf,  // Name of the buffer.
               const off_t  i,    // Offset of the buffer to read from.
               const size_t size) // The size in bytes to read from the buffer.
{
    return get(name)->read(buf, i, size);
}

// Write to window.
int wsys::write(const char  *name, // Name of the window.
                const char  *buf,  // Buffer to write from.
                const off_t  i,    // Offset of the buffer to write to.
                const size_t size) // The size in bytes to write to the buffer.
{
    return get(name)->write(buf, i, size);
}
