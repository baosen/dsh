#define FUSE_USE_VERSION 26
#include <list>
#include <fuse.h>
#include "zero.hpp"
#include "file.hpp"
using namespace std;

namespace {
    list<File> ents; // list of file entries.
}

// Do correct file operation according to the file type.
template<class F, class W>
int filedo(const char *path, F df, W wf) {
    // Check path for what kind of file is opened.
    const char *bs = path+1, *s;
    if ((s = strstr(bs, "dpy")))      // Is a display?
        return df(s);
    else if ((s = strstr(bs, "wnd"))) // Is a window?
        return wf(s);
    else
        return -EINVAL; // Invalid file name.
}

// Initialize desktop shell file system.
static void *dsh_init(struct fuse_conn_info *conn) noexcept
{
    return NULL;
}

// Create file.
static int dsh_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    // Caller can only create files of type dpy* and wnd*.
    return filedo(path, [](const char *p) {
        // Create new display.
        ents.emplace_back(File(p));
        return 0;
    }, [](const char *p) {
        // Create new window.
        ents.emplace_back(File(p));
        return 0;
    });
    return -EINVAL; // Invalid path.
}

// Get file attributes of a file in the shell file system.
static int dsh_getattr(const char *path, struct stat *buf) noexcept
{
    // Prepare stat-buffer.
    zero(*buf);
    // If caller wants to check the attributes of the backslash directory.
    if (!strcmp(path, "/")) {
        buf->st_mode = S_IFDIR | 0755; // Directory.
        buf->st_nlink = 0;             // Number of hardlinks that points to this file that exists in the file system.
        return 0;
    } 
    // See if the entry exists.
    for (const auto& e : ents) {
        if (!strcmp(path+1, e.name.c_str())) {
            buf->st_mode  = S_IFREG | 0444; // mode bits.
            buf->st_nlink = 0;
            buf->st_size  = 0;
            return 0;
        }
    }
    return -ENOENT;
}

// Read directory tree.
static int dsh_readdir(const char *path, void *buf, fuse_fill_dir_t fill, off_t offset, struct fuse_file_info *fi) 
{
    // Fill recursively.
    for (const auto& e : ents)
        // Build the file entries in the buffer.
        fill(buf, e.name.c_str(), nullptr, 0);
    return 0;
}

// Does the file exist in one of the entries?
static bool exists(const char *name) 
{
    for (const auto& e : ents)
        if (!strcmp(name, e.name.c_str()))
            return true;
    return false;
}

// Open the desktop shell file system.
static int dsh_open(const char *path, struct fuse_file_info *fi) noexcept
{
    return filedo(path, [&](const char *p) {
        if (!exists(p))
            return -ENOENT;
        //if ((fi->flags & O_ACCMODE) != O_RDONLY)
        //    return -EACCES;
    }, [&](const char *p) {
        if (!exists(p))
            return -ENOENT; // No entry found.
        //if ((fi->flags & O_ACCMODE) != O_RDONLY)
        //    return -EACCES; // Access denied.
    });
    return 0;
}

// Read file contents.
static int dsh_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) noexcept
{
    // Check if the path provided exist as a entry in the file entries.
    for (const auto& e : ents) {
        if (!strcmp(path+1, e.name.c_str())) {
            return filedo(path, [](const char *p) { // Display.
                // TODO.
                return 0;
            }, [](const char *p) { // Window.
                // TODO.
                return 0;
            });
        }
    }
    return -ENOENT;
}

// Write to display. Returns exactly the number of bytes written except on error.
static int dsh_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) noexcept
{
    for (const auto& e : ents) {
        if (!strcmp(path+1, e.name.c_str())) {
            return filedo(path, [](const char *p) { // Display.
                // TODO.
                return 0;
            }, [](const char *p) { // Window.
                // TODO.
                return 0;
            });
        }
    }
    return -ENOENT;
}

// Control files in shell file system.
static int dsh_ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) noexcept
{
    for (const auto& e : ents) {
        if (!strcmp(path+1, e.name.c_str())) {
            return filedo(path, [&](const char *p) {
                switch (cmd) {
                default:
                    break;
                }
                return 0;
            }, [&](const char *p) {
                switch (cmd) {
                default:
                    break;
                }
                return 0;
            });
        }
    }
    return -ENOENT;
}


// Make file node. Gets called for creation of all non-directory, non-symbolic link nodes.
int dsh_mknod(const char *path, mode_t mode, dev_t dev)
{
    puts("mknod");
    return -EINVAL;
}

// File system driver for displays.
int main(int argc, char *argv[])
{
    // Setup file system operations.
    static fuse_operations ops = {0};
    ops.init    = dsh_init;    // Initialize.
    ops.getattr = dsh_getattr; // Get attributes.
    ops.create  = dsh_create;  // Create file.
    ops.mknod   = dsh_mknod;   // Make file node.
    ops.open    = dsh_open;    // Open display to be worked upon.
    ops.read    = dsh_read;    // Read display's contents.
    ops.write   = dsh_write;   // Write to the display's contents.
    ops.ioctl   = dsh_ioctl;   // Control display.
    ops.readdir = dsh_readdir; // Read directory.

    // Start our engines!
    try {
        // Create file tree.
        ents.emplace_back(File("."));
        ents.emplace_back(File(".."));
        // Drive user-space file system.
        return fuse_main(argc, argv, &ops, nullptr);
    } catch (...) {
        return EXIT_FAILURE;
    }
}
