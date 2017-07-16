#include <list>
#include <cstring>
#include <sstream>
#include <iostream>
#include "zero.hpp"
#include "kbsys.hpp"
#include "msys.hpp"
#include "ssys.hpp"
#include "cmds.hpp"
#include "dsys.hpp"
#include "wsys.hpp"
#include "fs.hpp"
using namespace std;

// Return codes:
#define SUCCESS 0 // Operation successful.

// File entries in the file system.
static list<string> ents; // List of file entries.

// Do correct file operation according to the file type.
template<class F, class W, class K, class M> 
auto filedo(const char *path, // Path of the file.
            F           df,   // Function to call when the path points to a display file.
            W           wf,   // Function to call when the path points to a window file.
            K           kf,   // Function to call when the path points to a keyboard file.
            M           mf)   // Function to call when the path points to a mouse file.
{
    // Check path for what kind of file is opened.
    const char *bs = path+1, *s;
    // Is a display?
    if ((s = strstr(bs, "dpy")))
        // Call display function.
        return df(s);
    // Is a window?
    else if ((s = strstr(bs, "wnd")))
        // Call window function.
        return wf(s);
    // Is a keyboard?
    else if ((s = strstr(bs, "kb")))
        // Call keyboard function.
        return kf(s);
    // Is a mouse?
    else if ((s = strstr(bs, "m")))
        // Call mouse function.
        return mf(s);
    else
        // Invalid file name.
        return -EINVAL; 
}

// Do action if the path specified is in the file system.
template<class F> 
auto doifentry(const char *path, // Path of the file.
               F           f)    // Function to call if entry exists.
{
    for (const auto& e : ents)
        if (!strcmp(path+1, e.c_str()))
            return f();
    return -ENOENT;
}

// Initialize shell file system.
void* fs::init(struct fuse_conn_info *conn) noexcept 
{
    UNUSED(conn);
    return nullptr;
}

// Create shell file.
int fs::create(const char            *path, // File path.
               mode_t                 mode, // Create mode.
               struct fuse_file_info *fi)   // Other info that is not part of POSIX.
               noexcept
{
    // TODO: Store mode and set it.
    UNUSED(mode);

    // Force O_DIRECT (direct I/O, no caching).
    fi->direct_io = 1;

    // Caller can only create files of type dpy* and wnd*.
    return filedo(path, [](const char *p) {
        // TODO: Create new display.
        ents.emplace_back(p);
        return SUCCESS;
    }, [](const char *p) {
        // TODO: Create new window.
        ents.emplace_back(p);
        return SUCCESS;
    }, [&](const char *p) {
        ents.emplace_back(p);
        return SUCCESS;
    }, [](const char *p) {
        // TODO: Create new mouse.
        ents.emplace_back(p);
        return SUCCESS;
    });
    return -EINVAL; // Invalid path.
}

// Get file attributes of a file in the shell file system.
int fs::getattr(const char  *path,  // File path.
                struct stat *stbuf) // Buffer to fill the file attributes information.
                noexcept
{
    // Prepare stat-buffer.
    zero(*stbuf);

    // If caller wants to check the attributes of the backslash directory.
    if (!strcmp(path, "/")) {
        stbuf->st_mode = S_IFDIR | 0755; // Directory and its permission bits.
        stbuf->st_nlink = 0;             // Number of hardlinks that points to this file that exists in the file system.
        return SUCCESS;
    } 

    // Check if the file system has it as a file entry.
    return doifentry(path, [&]() {
        stbuf->st_mode  = S_IFREG | 0444; // File and its permission bits.
        stbuf->st_nlink = 0;              // Hard links.
        stbuf->st_size  = 0;              // uhm... size of file?
        return SUCCESS;
    });
}

// Read current tree of the mounted directory.
int fs::readdir(const char            *path,   // File path.
                void                  *buf,    // The returned buffer to fill the file entries.
                fuse_fill_dir_t        fill,   // Function to call to fill the provided buffer with entries.
                off_t                  offset, // Offset to place??
                struct fuse_file_info *fi)     // Other info about the file.
                noexcept
{
    UNUSED(path);
    UNUSED(offset);
    UNUSED(fi);

    // Fill recursively.
    for (const auto& e : ents) {
        // Build the file entries in the buffer.
        if (fill(buf, e.c_str(), 0, 0) == 1) // Is buffer full?
            return -ENOBUFS;
    }
    return SUCCESS;
}

// Open the shell file system.
int fs::open(const char            *path, // Path to file to open.
             struct fuse_file_info *fi)   // Other file info.
             noexcept 
{

    // Force O_DIRECT (direct I/O, no caching).
    fi->direct_io = 1;

    // Check if a file exist and open it.
    return doifentry(path, [&] {
        return SUCCESS;
    });
}

// Read file contents. Returns number of bytes read.
int fs::read(const char            *path, // Pathname of the file to read.
             char                  *buf,  // Buffer to fill with the file contents read.
             size_t                 size, // The amount of bytes to read.
             off_t                  i,    // The offset to read the data from.
             struct fuse_file_info *fi)   // Other info about the file read.
             noexcept 
{
    UNUSED(fi);

    // Do file read if the asked entry exists.
    return doifentry(path, [&]() {
        return filedo(path, [&](const char *name) { // Display.
            UNUSED(name);
            // Read from display.
            dsys::read(name, buf, i, size);
            return SUCCESS;
        }, [&](const char *name) {                  // Window.
            UNUSED(name);
            // Read from window.
            wsys::read(name, buf, i, size);
            return SUCCESS;
        }, [&](const char *name) {                  // Keyboard.
            UNUSED(name);
            // Check if the read is not whole (divisible).
            const auto isize = sizeof(input_event);
            if (isize % size != 0)
                return -EINVAL; // Invalid parameter.

            // Read keyboard input event from keyboard.
            const auto n = isize / size;
            int read = 0;
            for (uint i = 0; i < n; ++i) {
                const auto e = kbsys::get();
                memcpy(buf, &e, sizeof(input_event));
                buf  += isize;
                read += isize;
            }
            // Return number of bytes read.
            return read;
        }, [&](const char *name) {                  // Mouse.
            UNUSED(name);
            // Read from mouse.
            if (sizeof(msys::Ev) % size != 0)
                return -EINVAL;

            // Copy mouse event into the buffer.
            return msys::getmot(buf, size / sizeof(msys::Ev));
        });
    });
}

// Write to file. Returns exactly the number of bytes written except on error.
int fs::write(const char            *path, // Path to the file to be written to.
              const char            *buf,  // The buffer containing the data to write.
              size_t                 size, // The size in bytes to write.
              off_t                  i,    // The offset to write to.
              struct fuse_file_info *fi)   // Other info about the file read.
              noexcept 
{
    UNUSED(fi);

    return doifentry(path, [&]() {
        return filedo(path, [&](const char *name) { // Display.
            // Write to display in the display/screen's pixel format.
            dsys::write(name, buf, i, size);
            return SUCCESS;
        }, [&](const char *name) {                  // Window.
            UNUSED(name);
            // Write to window in the display/screen's pixel format.
            wsys::write(name, buf, i, size);
            return SUCCESS;
        }, [](const char *name) {                   // Keyboard.
            UNUSED(name);
            // Keyboard is read-only.
            return -EPERM; // Operation not permitted.
        }, [](const char *name) {
            UNUSED(name);
            // Mouse is read-only.
            return -EPERM; // Operation not permitted.
        });
    });
}

// Control a file.
int fs::ioctl(const char            *path,  // Path of the file to control.
              int                    cmd,   // The ioctl() command number passed.
              void                  *arg,   // The arguments provided to the ioctl() call.
              struct fuse_file_info *fi,    // Other info.
              unsigned int           flags, // File flags ??
              void                  *data)  // ??
              noexcept                      // This function cannot throw an exception.
{
    UNUSED(arg);
    UNUSED(fi);
    UNUSED(flags);
    UNUSED(data);

    // Do if path entry exist in the file entries.
    return doifentry(path, [&]() {
        return filedo(path, [&](const char *name) { // Display.
            UNUSED(name);
            return dpycmd(cmd);
        }, [&](const char *name) {                  // Window.
            UNUSED(name);
            return wndcmd(cmd);
        }, [](const char *name) {                   // Keyboard.
            UNUSED(name);
            // No commands for keyboards.
            return -EINVAL;
        }, [](const char *name) {
            UNUSED(name);
            // TODO: Currently no commands for keyboards.
            return -EINVAL;
        });
    });
}

// Make shell file node. Gets called for creation of all non-directory, non-symbolic link nodes.
int fs::mknod(const char *path, // File path.
              mode_t      mode, // Mode to set the newly created file node.
              dev_t       dev)  // Optional device provided.
              noexcept 
{
    UNUSED(dev);

    return create(path, mode, nullptr);
}

// Create standard "this" and "parent" links.
static void mklns() 
{
    // Set link to current directory.
    ents.emplace_back(".");
    // Set link to parent directory.
    ents.emplace_back("..");
}

// Make the default numbered files at start.
#define MKFILES(name) \
    static uint i = 0; /* Current index of the keyboard. */ \
    stringstream ss; \
    ss << name << i; \
    ents.emplace_back(ss.str()); 

// Make the file that contain the color bit depth per component, which is used for all things graphics.
static void mkcfmt() 
{
    ents.emplace_back("r"); // contains color bit depth for red component.
    ents.emplace_back("g"); // contains color bit depth for green component.
    ents.emplace_back("b"); // contains color bit depth for blue component.
    ents.emplace_back("a"); // contains color bit depth for alpha component.
}

// Setup and initialize displays, and make the files pointing to them.
static void mkdpys() 
{
    // Initialize graphical output.
    dsys::init();
    // Insert it into filesystem.
    MKFILES("dpy")
    // Make file that show the color format.
    mkcfmt();
}

// Setup mouse and make mouse files.
static void mkm() 
{
    // Initialize mouse.
    msys::init();
    // Insert it into filesystem.
    MKFILES("m")
}

// Setup keyboard and make keyboard files.
static void mkkb() 
{
    // Initialize keyboard.
    kbsys::init();
    // Insert it into filesystem.
    MKFILES("kb")
}

// Setup and make sound files.
static void mksnd() 
{
    // Initialize sound system.
    ssys::init();
    // Insert it into filesystem.
    MKFILES("snd")
}

// Setup and make windows.
static void mkw() 
{
    // Initialize windows.
    wsys::init();
    // Insert it into filesystem.
    MKFILES("wnd")
}

// Cleanup filesystem.
void fs::cleanup() 
{
    // Cleanup keyboard.
    kbsys::deinit();
    // Cleanup mouse.
    msys::deinit();

/*
    // Cleanup display.
    dsys::deinit();
    // Cleanup sound.
    ssys::deinit();
    // Cleanup window.
    wsys::deinit();
*/
}

// Setup shell.
void fs::setup() 
{
    // Create standard "this" and "parent" links in the file system tree.
    mklns();
    // Connect keyboards and make keyboard files.
    mkkb();
    // Connect mouse and make mouse files.
    mkm();

/*
    // Connect to displays and make them as files.
    mkdpys();
*/
}
