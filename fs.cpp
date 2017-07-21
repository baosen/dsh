#include "zero.hpp"
#include "kbsys.hpp"
#include "msys.hpp"
#include "dir.hpp"
#include "kbf.hpp"
#include "mf.hpp"
#include "wndx.hpp"
#include "wndy.hpp"
#include "errno.hpp"
using namespace std;

// Initializer list of file system entries.
typedef initializer_list<shared_ptr<ent>> entries;

// Make shared pointer to a directory.
#define dirp make_shared<dir>
#define filep(type) make_shared<type>

// File tree.
static dir root { // TODO: Remove root directory, which I think is unnecessary.
    "/",          // Root directory.
    { 
        dirp (    
            "kb", 
            entries { 
                filep(kbf)("0")
            }
        ),
        dirp (   
            "m", 
            entries { 
                filep(mf)("0")
            }
        ),
        dirp (
            "wnd",
            entries {
                dirp (
                    "0", 
                    entries {
                        filep(wndx)(),
                        filep(wndy)()
                    }
                )
            }
        )
    }
};

// File entries in the file system.
static list<string> ents; // List of file entries.

// Initialize shell file system.
void* fs::init(struct fuse_conn_info *conn)  
{
    // Setup shell.
    setup();
    return nullptr;
}

// Destroy shell file system.
void fs::destroy(void* p) 
{
    UNUSED(p);
    // Cleanup subsystems.
    cleanup();
}

// Create shell file.
int fs::create(const char            *path, // File path.
               mode_t                 mode, // Create mode.
               struct fuse_file_info *fi)   // Other info that is not part of POSIX.
{
    // TODO: Store mode and set it.
    UNUSED(mode);

    // Force O_DIRECT (direct I/O, no caching).
    fi->direct_io = 1;

    // TODO: Caller can only create files of type dpy* and wnd*.

    return -EINVAL; // Invalid parameter.
}

// Get file attributes of a file in the shell file system.
int fs::getattr(const  char  *path,  // File path.
                struct stat  *stbuf) // Buffer to fill the file attributes information.
{
    // Prepare stat-buffer.
    zero(*stbuf);

    // If caller wants to check the attributes of the root (main) directory of the file system (backslash directory).
    if (!strcmp(path, "/")) {
        stbuf->st_mode = S_IFDIR | 0755; // Is a directory ORed with the permission bits.
        stbuf->st_nlink = 0;             // Number of hardlinks that points to this file that exists in the file system.
        return SUCCESS;
    } 

    // Check if the file system has it as a file entry.
    const auto e = root.getent(path);

    // Found entry?
    if (!*e)
        return -ENOENT; // No entry found.

    stbuf->st_mode  = e->mode;  // File and its permission bits.
    stbuf->st_nlink = e->nlink; // Hard links.
    stbuf->st_size  = 0;        // uhm... size of file?

    return SUCCESS;
}

#define BUFFULL 1 // Is buffer full?

// Read the current file tree of the directory of the mounted file system.
int fs::readdir(const char            *path,   // File path.
                void                  *buf,    // The returned buffer to fill with file entries.
                fuse_fill_dir_t        fill,   // Function to call to fill the provided buffer with entries.
                off_t                  offset, // Offset to place??
                struct fuse_file_info *fi)     // Other info about the file.
{
    UNUSED(path);
    UNUSED(offset);
    UNUSED(fi);

    // Get directory from file path.
    const auto e = root.getdir(path);
    if (!*e)
        return -ENOENT;

    // Fill buffer with file entries.
    for (const auto& f : e->files)
        // Build the file entries in the buffer.
        if (fill(buf, f->name.c_str(), 0, 0) == BUFFULL) // Is buffer full?
            return -ENOBUFS;

    // Operation successful.
    return SUCCESS;
}

// Open the shell file system.
int fs::open(const char            *path, // Path to file to open.
             struct fuse_file_info *fi)   // Other file info.
{
    // Force O_DIRECT (direct I/O, no caching).
    fi->direct_io = 1;

    // Check if a file exist and open it.
    const auto e = root.getent(path);

    // No such file or directory?
    if (!*e)
        return -ENOENT;

    // Try to open it!
    return e->open(path);
}

// Read file contents. Returns number of bytes read.
int fs::read(const char            *path,   // Pathname of the file to read.
             char                  *buf,    // Buffer to fill with the file contents read.
             const size_t           nbytes, // The number of bytes to read.
             const off_t            i,      // The offset to read the data from.
             struct fuse_file_info *fi)     // Other info about the file read.
{
    UNUSED(fi);
    // TODO: Use file descriptor instead for performance?

    auto e = root.getfile(path);
    if (!*e)
        return -ENOENT;
    return e->read(buf, i, nbytes);
}

// Write to file. Returns exactly the number of bytes written, except on error.
int fs::write(const char            *path,   // Path to the file to be written to.
              const char            *buf,    // The buffer containing the data to write.
              const size_t           nbytes, // The number of bytes to write.
              const off_t            i,      // The offset to write to.
              struct fuse_file_info *fi)     // Other info about the file read.
{
    UNUSED(fi);
    // TODO: Use file descriptor instead for performance?
    
    auto e = root.getfile(path);
    if (!*e)
        return -ENOENT;
    return e->write(buf, i, nbytes);
}

// Control a file.
int fs::ioctl(const char            *path,  // Path of the file to control.
              int                    cmd,   // The ioctl() command number passed.
              void                  *arg,   // The arguments provided to the ioctl() call.
              struct fuse_file_info *fi,    // Other info.
              unsigned int           flags, // File flags ??
              void                  *data)  // ??
{
    UNUSED(arg);
    UNUSED(fi);
    UNUSED(flags);
    UNUSED(data);
    return -EPERM;
}

// Make shell file node. Gets called for creation of all non-directory, non-symbolic link nodes.
int fs::mknod(const char *path, // File path.
              mode_t      mode, // Mode to set the newly created file node.
              dev_t       dev)  // Optional device provided.
{
    UNUSED(dev);
    return create(path, mode, nullptr);
}

/*
// Make the file that contain the color bit depth per component, which is used for all things graphics.
static void mkcfmt() 
{
    ents.emplace_back("r"); // contains color bit depth for red component.
    ents.emplace_back("g"); // contains color bit depth for green component.
    ents.emplace_back("b"); // contains color bit depth for blue component.
    ents.emplace_back("a"); // contains color bit depth for alpha component.
}
*/

/*
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
*/

// Setup shell file system.
void fs::setup() 
{
    // Initialize keyboard.
    kbsys::init();
    // Initialize mouse.
    msys::init();
/*
    // Connect to displays and make them as files.
    mkdpys();
*/
}

// Cleanup shell file system.
void fs::cleanup() 
{
    // Has it been called once?
    static bool called = false;

    // Check if cleanup has been called once.
    if (called)
        return;

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

    called = true;
}
