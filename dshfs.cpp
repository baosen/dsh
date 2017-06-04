// Shell server-side file system.
#define FUSE_USE_VERSION 26
#include <list>
#include <sstream>
#include <fuse.h>
#include "zero.hpp"
#include "log.hpp"
#include "file.hpp"
#include "kbsys.hpp"
#include "msys.hpp"
#include "fs.hpp"
#include "cmds.hpp"
#include "dpysys.hpp"
using namespace std;

namespace {
    list<File> ents; // List of file entries.
}

// Do correct file operation according to the file type.
template<class F, class W, class K> auto filedo(const char *path, F df, W wf, K kf) {
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
template<class F> auto doifentry(const char *path, F f) {
    for (const auto& e : ents)
        if (!strcmp(path+1, e.name.c_str()))
            return f();
    return -ENOENT;
}

namespace fs {
    // Initialize desktop shell file system.
    void *init(struct fuse_conn_info *conn) noexcept {
        return nullptr;
    }
    
    // Create shell file.
    int create(const char *path, mode_t mode, struct fuse_file_info *fi) {
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
    int getattr(const char *path, struct stat *buf) noexcept {
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
    int readdir(const char *path, void *buf, fuse_fill_dir_t fill, off_t offset, struct fuse_file_info *fi) {
        // Fill recursively.
        for (const auto& e : ents)
            // Build the file entries in the buffer.
            fill(buf, e.name.c_str(), nullptr, 0);
        return 0;
    }
    
    // Does the file exist in one of the entries?
    bool exists(const char *name) {
        for (const auto& e : ents)
            if (!strcmp(name, e.name.c_str()))
                return true;
        return false;
    }
    
    // Open the desktop shell file system.
    int open(const char *path, struct fuse_file_info *fi) noexcept {
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
    int read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) noexcept {
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
    int write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) noexcept {
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
    
    // Control files in shell file system.
    int ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) noexcept {
        return doifentry(path, [&]() {
            return filedo(path, [&](const char *p) { // Display.
                return dpycmd(cmd);
            }, [&](const char *p) {                  // Window.
                return wndcmd(cmd);
            }, [&](const char *p) {                  // Keyboard.
                // No commands for keyboards.
                return -EINVAL;
            });
        });
    }
    
    // Make shell file node. Gets called for creation of all non-directory, non-symbolic link nodes.
    int mknod(const char *path, mode_t mode, dev_t dev) {
        return create(path, mode, nullptr);
    }
    
    // Create standard "this" and "parent" links.
    void mklns() {
        ents.emplace_back(File("."));
        ents.emplace_back(File(".."));
    }
    
    // Setup and initialize displays, and make the files pointing to them.
    void mkdpys() {
        // Initialize graphical output.
        dpyinit();
        static uint i = 0; // Current index of display.
        stringstream ss;
        ss << "dpy" << i;
        ents.emplace_back(File(ss.str()));
    }
    
    // Setup mouse and make mouse files.
    void mkm() {
        // Initialize mouse.
        initm();
        // Make mouse files.
        static uint i = 0;
        stringstream ss;
        ss << "m" << i;
        ents.emplace_back(File(ss.str()));
    }
    
    // Setup keyboard.
    void mkkb() {
        // Initialize keyboard.
        initkb();
        // Insert it into filesystem.
        static uint i = 0; // Current index of keyboard.
        stringstream ss;
        ss << "kb" << i;
        ents.emplace_back(File(ss.str()));
    }
    
    void cleanup() {
        // TODO: Cleanup keyboard, sound, mouse.
        dpydeinit();
    }
}

// File system driver for displays.
int main(int argc, char *argv[]) {
    using namespace fs;

    // Setup file system operations.
    static fuse_operations ops = {0};
    // Creation.
    ops.init    = init;      // Initialize file system.
    ops.create  = create;    // Create file.
    ops.mknod   = fs::mknod; // Make file node.
    // I/O.
    ops.getattr = getattr; // Get attributes.
    ops.readdir = readdir; // Read directory.
    ops.open    = open;    // Open display to be worked upon.
    ops.read    = read;    // Read display's contents.
    ops.write   = write;   // Write to the display's contents.
    // Control.
    ops.ioctl   = ioctl;   // Control display.

    // Start our engines!
    try {
        // Create standard "this" and "parent" links in the file system tree.
        mklns();
        // TODO: Connect keyboards and make keyboard files.
        mkkb();
        // TODO: Connect mouse and make mouse files.
        mkm();
        // TODO: Connect to displays and make them as files.
        mkdpys();
        // Drive user-space file system.
        return fuse_main(argc, argv, &ops, nullptr);
    } catch (...) {
        error("Exception caught!");
    }
    cleanup();
    return EXIT_FAILURE;
}
