#include <list>
#include <unordered_map>
#include <string>
#include <memory>
#include "wsys.hpp"
#include "mwnd.hpp"
using namespace std;

namespace {
    unordered_map<string, unique_ptr<Wnd>> wnds;
}

// Initialize and setup window system.
void wsys::init() 
{
    // Add a single window.
    wnds["wnd0"] = unique_ptr<Wnd>(new Mwnd());
}

// Deinitialize the window system.
void wsys::deinit() 
{
    wnds.clear();
}

// Read from window.
void wsys::read(const char  *name, // Name of the window.
                const char  *buf,  // Name of the buffer.
                const off_t  i,    // Offset of the buffer to read from.
                const size_t size) // The size in bytes to read from the buffer.
{
    // TODO!
    wnds[name];
}

// Write to window.
void wsys::write(const char  *name, // Name of the window.
                 const char  *buf,  // Name of the buffer.
                 const off_t  i,    // Offset of the buffer to write to.
                 const size_t size) // The size in bytes to write to the buffer.
{
    // TODO!
    wnds[name];
}
