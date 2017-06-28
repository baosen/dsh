#include <list>
#include "zero.hpp"
#include "kbsys.hpp"
#include "msys.hpp"
#include "ssys.hpp"
#include "cmds.hpp"
#include "dsys.hpp"
#include "wsys.hpp"
#include "fs.hpp"
using namespace std;

// File entries in the file system.
namespace {
    list<string> ents; // List of file entries.

    // Does the file exist in one of the entries?
    bool exists(const char *name) 
    {
        // Find the file in the list of file entries.
        for (const auto& e : ents)
            if (!strcmp(name, e.c_str()))
                return true;
        return false;
    }
}

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
    return nullptr;
}

// Create shell file.
int fs::create(const char            *path, // File path.
               mode_t                 mode, // Create mode.
               struct fuse_file_info *fi)   // Other info that is not part of POSIX.
               noexcept
{
    // Caller can only create files of type dpy* and wnd*.
    return filedo(path, [](const char *p) {
        // TODO: Create new display.
        ents.emplace_back(p);
        return 0;
    }, [](const char *p) {
        // TODO: Create new window.
        ents.emplace_back(p);
        return 0;
    }, [](const char *p) {
        // TODO: Create new keyboard.
        ents.emplace_back(p);
        return 0;
    }, [](const char *p) {
        // TODO: Create new mouse.
        ents.emplace_back(p);
        return 0;
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
        return 0;
    } 
    // It is a file entry.
    return doifentry(path, [&]() {
        stbuf->st_mode  = S_IFREG | 0444; // File and its permission bits.
        stbuf->st_nlink = 0;              // Hard links.
        stbuf->st_size  = 0;              // uhm... size of file?
        return 0;
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
    // Fill recursively.
    for (const auto& e : ents) {
        // Build the file entries in the buffer.
        if (fill(buf, e.c_str(), 0, 0) == 1) // is buffer full?
            return -ENOBUFS;
    }
    return 0;
}

// Check if the entry name given exist in the file tree.
#define ENTRYCHK \
    if (!exists(p)) \
        return -ENOENT; // No entry found.

// Open the shell file system.
int fs::open(const char            *path, // Path to file to open.
             struct fuse_file_info *fi)   // Other file info.
             noexcept 
{
    return filedo(path, [](const char *p) {
        ENTRYCHK
    }, [](const char *p) {
        ENTRYCHK
    }, [](const char *p) {
        ENTRYCHK
    }, [](const char *p) {
        ENTRYCHK
    });
    return 0;
}

// Read file contents.
int fs::read(const char            *path, // Pathname of the file to read.
             char                  *buf,  // Buffer to fill with the file contents read.
             size_t                 size, // The amount of bytes to read.
             off_t                  i,    // The offset to read the data from.
             struct fuse_file_info *fi)   // Other info about the file read.
             noexcept 
{
    // Do file read if the asked entry exists.
    return doifentry(path, [&]() {
        return filedo(path, [&](const char *p) { // Display.
            // Read from display.
            dsys::read(p, buf, i, size);
            return 0;
        }, [&](const char *p) {                  // Window.
            // Read from window.
            wsys::read(p, buf, i, size);
            return 0;
        }, [&](const char *p) {                  // Keyboard.
            // Read key code from keyboard.
            if (sizeof(Kb::Kbc) < size)
                return -EINVAL; // Invalid parameter.
            const auto c = kbsys::kb.get();
            memcpy(buf, &c, sizeof(Kb::Kbc));
            return 0;
        }, [&](const char *p) {                  // Mouse.
            // Read from mouse.
            if (sizeof(uint)*2 < size)
                return -EINVAL; // Invalid parameter.
            // Copy mouse event into the buffer.
            msys::copymot(buf, size);
            return 0;
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
    return doifentry(path, [&]() {
        return filedo(path, [&](const char *name) { // Display.
            // Write to display in the display/screen's pixel format.
            dsys::write(name, buf, i, size);
            return 0;
        }, [&](const char *name) {                  // Window.
            // Write to window in the display/screen's pixel format.
            wsys::write(name, buf, i, size);
            return 0;
        }, [](const char *name) {                   // Keyboard.
            // Keyboard is read-only.
            return -EPERM; // Operation not permitted.
        }, [](const char *name) {
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
    // Do if path entry exist in the file entries.
    return doifentry(path, [&]() {
        return filedo(path, [&](const char *name) { // Display.
            return dpycmd(cmd);
        }, [&](const char *name) {                  // Window.
            return wndcmd(cmd);
        }, [](const char *name) {                   // Keyboard.
            // No commands for keyboards.
            return -EINVAL;
        }, [](const char *name) {
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
    return create(path, mode, nullptr);
}

namespace {
    // Create standard "this" and "parent" links.
    void mklns() 
    {
        // Set link to current directory.
        ents.emplace_back(".");
        // Set link to parent directory.
        ents.emplace_back("..");
    }

// Make the default numbered files at start.
#define MKFILES(name) \
    static uint i = 0; // Current index of the keyboard. \
    stringstream ss; \
    ss << "name" << i; \
    ents.emplace_back(ss.str()); 

    // Make file that contain the color bit depth per component, which is used for all things graphics.
    void mkcfmt() 
    {
        ents.emplace_back("r"); // contains color bit depth for red component.
        ents.emplace_back("g"); // contains color bit depth for green component.
        ents.emplace_back("b"); // contains color bit depth for blue component.
        ents.emplace_back("a"); // contains color bit depth for alpha component.
    }
    
    // Setup and initialize displays, and make the files pointing to them.
    void mkdpys() 
    {
        // Initialize graphical output.
        dsys::init();
        // Insert it into filesystem.
        MKFILES(dpy)
        // Make file that show the color format.
        mkcfmt();
    }
    
    // Setup mouse and make mouse files.
    void mkm() 
    {
        // Initialize mouse.
        msys::init();
        // Insert it into filesystem.
        MKFILES(m)
    }
    
    // Setup keyboard and make keyboard files.
    void mkkb() 
    {
        // Initialize keyboard.
        kbsys::init();
        // Insert it into filesystem.
        MKFILES(kb)
    }

    // Setup and make sound files.
    void mksnd() 
    {
        // Initialize sound system.
        ssys::init();
        // Insert it into filesystem.
        MKFILES(snd)
    }

    // Setup and make windows.
    void mkw() 
    {
        // Initialize windows.
        wsys::init();
        // Insert it into filesystem.
        MKFILES(wnd)
    }
}

// Cleanup filesystem.
void fs::cleanup() 
{
    // Cleanup display.
    dsys::deinit();
    // Cleanup mouse.
    msys::deinit();
    // Cleanup keyboard.
    kbsys::deinit();
    // Cleanup mouse.
    msys::deinit();
    // Cleanup sound.
    ssys::deinit();
    // Cleanup window.
    wsys::deinit();
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
    // Connect to displays and make them as files.
    mkdpys();
}
