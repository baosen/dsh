// Shell server-side file system.
#define FUSE_USE_VERSION 26
#include <list>
#include <iostream>
#include <sstream>
#include <memory>
#include <fuse.h>
#include "zero.hpp"
#include "file.hpp"
#include "dpycmds.hpp"
#include "wcmds.hpp"
#include "kbsys.hpp"
#include "fs.hpp"
using namespace std;

namespace {
    list<File>      ents;     // List of file entries.
    unique_ptr<Dpy> dpys;     // Displays connected to the computer.
}

// Do correct file operation according to the file type.
template<class F, class W, class K>
auto filedo(const char *path, F df, W wf, K kf) {
    // Check path for what kind of file is opened.
    const char *bs = path+1, *s;
    if ((s = strstr(bs, "dpy")))      // Is a display?
        return df(s);
    else if ((s = strstr(bs, "wnd"))) // Is a window?
        return wf(s);
    else if ((s = strstr(bs, "kb")))  // Is a keyboard?
        return kf(s);
    else
        return -EINVAL; // Invalid file name.
}

// Do action if the path specified is in the file system.
template<class F> 
auto doifentry(const char *path, F f) {
    for (const auto& e : ents)
        if (!strcmp(path+1, e.name.c_str()))
            return f();
    return -ENOENT;
}

// Initialize desktop shell file system.
static void *dsh_init(struct fuse_conn_info *conn) noexcept {
    return nullptr;
}

// Create shell file.
static int dsh_create(const char *path, mode_t mode, struct fuse_file_info *fi) {
    // Caller can only create files of type dpy* and wnd*.
    return filedo(path, [](const char *p) {
        // Create new display.
        ents.emplace_back(File(p));
        return 0;
    }, [](const char *p) {
        // Create new window.
        ents.emplace_back(File(p));
        return 0;
    }, [](const char *p) {
        // Create new keyboard.
        ents.emplace_back(File(p));
        return 0;
    });
    return -EINVAL; // Invalid path.
}

// Get file attributes of a file in the shell file system.
static int dsh_getattr(const char *path, struct stat *buf) noexcept {
    // Prepare stat-buffer.
    zero(*buf);
    // If caller wants to check the attributes of the backslash directory.
    if (!strcmp(path, "/")) {
        buf->st_mode = S_IFDIR | 0755; // Directory.
        buf->st_nlink = 0;             // Number of hardlinks that points to this file that exists in the file system.
        return 0;
    } 
    return doifentry(path, [&]() {
        buf->st_mode  = S_IFREG | 0444; // mode bits.
        buf->st_nlink = 0;
        buf->st_size  = 0;
        return 0;
    });
}

// Read directory tree.
static int dsh_readdir(const char *path, void *buf, fuse_fill_dir_t fill, off_t offset, struct fuse_file_info *fi) {
    // Fill recursively.
    for (const auto& e : ents)
        // Build the file entries in the buffer.
        fill(buf, e.name.c_str(), nullptr, 0);
    return 0;
}

// Does the file exist in one of the entries?
static bool exists(const char *name) {
    for (const auto& e : ents)
        if (!strcmp(name, e.name.c_str()))
            return true;
    return false;
}

// Open the desktop shell file system.
static int dsh_open(const char *path, struct fuse_file_info *fi) noexcept {
    return filedo(path, [&](const char *p) {
        if (!exists(p))
            return -ENOENT;
    }, [&](const char *p) {
        if (!exists(p))
            return -ENOENT; // No entry found.
    }, [](const char *p) {
        if (!exists(p))
            return -ENOENT;
    });
    return 0;
}

// Read file contents.
static int dsh_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) noexcept {
    return doifentry(path, [&]() {
        return filedo(path, [](const char *p) { // Display.
            // TODO.
            return 0;
        }, [](const char *p) {                  // Window.
            // TODO.
            return 0;
        }, [](const char *p) {                  // Keyboard.
            // Read key code.
            return kb.get();
        });
    });
}

// Write to display. Returns exactly the number of bytes written except on error.
static int dsh_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) noexcept {
    return doifentry(path, [&]() {
        return filedo(path, [](const char *p) { // Display.
            // TODO.
            return 0;
        }, [](const char *p) {                  // Window.
            // TODO.
            return 0;
        }, [](const char *p) {                  // Keyboard.
            // Keyboard is read-only.
            return -EPERM; // Operation not permitted.
        });
    });
}

// Do display command.
static int dpycmd(const int cmd) {
    switch (cmd) {
    case Dpycmd::reset:
        return 0;
    case Dpycmd::hz:
        return 0;
    case Dpycmd::res:
        return 0;
    default:
        break;
    };
    return -EINVAL;
}

// Do window command.
static int wndcmd(const int cmd) {
    switch (cmd) {
    case Wndcmd::max:   // User wants to maximize window.
        return 0;
    case Wndcmd::min:   // User wants to minimize window.
        return 0;
    case Wndcmd::click: // User clicks somewhere on the window.
        return 0;
    case Wndcmd::copy:  // User wants to copy an existing rectangular image to a window. Sends a raw or compressed rectangular image. User chooses driver.
        return 0;
    default:
        break;
    }
    return -EINVAL;
}

// Control files in shell file system.
static int dsh_ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) noexcept {
    return doifentry(path, [&]() {
        return filedo(path, [&](const char *p) { // display.
            return dpycmd(cmd);
        }, [&](const char *p) { // window.
            return wndcmd(cmd);
        }, [&](const char *p) {
            // No commands for keyboards.
            return -EINVAL;
        });
    });
}

// Make shell file node. Gets called for creation of all non-directory, non-symbolic link nodes.
static int dsh_mknod(const char *path, mode_t mode, dev_t dev) {
    return dsh_create(path, mode, nullptr);
}

// Create standard "this" and "parent" links.
static void mkstdlinks() {
    ents.emplace_back(File("."));
    ents.emplace_back(File(".."));
}

// Setup and initialize displays, and make the files pointing to them.
static void mkdpys() {
// Initialize graphical output.
#ifdef DRM
    // Use DRM graphical output.
#elif FB
    // Use framebuffer graphical output.
#else
//#   error No screen output chosen. Choose one to continue compiling.
#endif
    static uint i = 0; // Current index of display.
    stringstream ss;
    ss << "dpy" << i;
    ents.emplace_back(File(ss.str()));
}

// Setup keyboard.
static void mkkb() {
    // Initialize keyboard.
    //initkb();

    // Insert it into filesystem.
    static uint i = 0; // Current index of keyboard.
    stringstream ss;
    ss << "kb" << i;
    ents.emplace_back(File(ss.str()));
}

// File system driver for displays.
int main(int argc, char *argv[]) {
    // Setup file system operations.
    static fuse_operations ops = {0};
    // Creation.
    ops.init    = dsh_init;    // Initialize file system.
    ops.create  = dsh_create;  // Create file.
    ops.mknod   = dsh_mknod;   // Make file node.
    // I/O.
    ops.getattr = dsh_getattr; // Get attributes.
    ops.readdir = dsh_readdir; // Read directory.
    ops.open    = dsh_open;    // Open display to be worked upon.
    ops.read    = dsh_read;    // Read display's contents.
    ops.write   = dsh_write;   // Write to the display's contents.
    // Control.
    ops.ioctl   = dsh_ioctl;   // Control display.

    // Start our engines!
    try {
        // Create standard "this" and "parent" links in the file system tree.
        mkstdlinks();
        // TODO: Connect keyboards and make keyboard files.
        mkkb();
        // TODO: Connect to displays and make them as files.
        mkdpys();

        // Drive user-space file system.
        return fuse_main(argc, argv, &ops, nullptr);
    } catch (...) {
        return EXIT_FAILURE;
    }
}
