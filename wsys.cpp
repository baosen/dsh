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

uint wsys::getx(const char *name)
{
    return wnds[name]->pcur.x;
}

uint wsys::gety(const char *name)
{
    return wnds[name]->pcur.y;
}

void wsys::movex(const char *name, const uint x)
{
    wnds[name]->movex(x);
}

void wsys::movey(const char *name, const uint y)
{
    wnds[name]->movey(y);
}

// Read from window.
int wsys::read(const char  *name, // Name of the window.
               void        *buf,  // Name of the buffer.
               const off_t  i,    // Offset of the buffer to read from.
               const size_t size) // The size in bytes to read from the buffer.
{
    // TODO: What happens if it does not exists?
    return wnds[name]->read(buf, i, size);
}

// Write to window.
int wsys::write(const char  *name, // Name of the window.
                const char  *buf,  // Buffer to write from.
                const off_t  i,    // Offset of the buffer to write to.
                const size_t size) // The size in bytes to write to the buffer.
{
    // TODO: What happens if it does not exists?
    return wnds[name]->write(buf, i, size);
}
