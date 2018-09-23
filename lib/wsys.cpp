#include "bg.hpp"
#include "wsys.hpp"
using namespace std;

// Windows managed by the windowing subsystem.
static unordered_map<string, unique_ptr<wnd>> wnds;

// Initialize and setup window system.
void wsys::init() 
{
    // Create background window.
    wnds["0"] = make_unique<bg>();

    // Create a single window.
    wnds["1"] = make_unique<wnd>(pos(0, 0), 
                                 res(100, 100));
}

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

// Get X position of window.
uint wsys::getx(const char *name)
{
    return get(name)->pcur.x;
}

// Get Y position of window.
uint wsys::gety(const char *name)
{
    return get(name)->pcur.y;
}

// Get color properties of a window.
prop wsys::getcp(const char *name)
{
    return get(name)->cp();
}

// Get move window.
void wsys::move(const char *name, const pos& p)
{
    get(name)->move(p);
}

// Get move x window.
void wsys::movex(const char *name, const uint x)
{
    get(name)->movex(x);
}

// Get move y window.
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
