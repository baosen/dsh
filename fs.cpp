// Shell server-side file system.
#include <list>
#include <sstream>
#include "zero.hpp"
#include "file.hpp"
#include "kbsys.hpp"
#include "msys.hpp"
#include "cmds.hpp"
#include "dsys.hpp"
#include "wsys.hpp"
#include "fs.hpp"
using namespace std;

// File entries in the file system.
namespace {
    list<File> ents; // List of file entries.
    // Does the file exist in one of the entries?
    bool exists(const char *name) {
        for (const auto& e : ents)
            if (!strcmp(name, e.name.c_str()))
                return true;
        return false;
    }
}

// Do correct file operation according to the file type.
template<class F, class W, class K> auto filedo(const char *path, F df, W wf, K kf) {
    // Check path for what kind of file is opened.
    const char *bs = path+1, *s;
    // Is a display?
    if ((s = strstr(bs, "dpy")))
        return df(s);
    // Is a window?
    else if ((s = strstr(bs, "wnd")))
        return wf(s);
    // Is a keyboard?
    else if ((s = strstr(bs, "kb")))
        return kf(s);
    else
        // Invalid file name.
        return -EINVAL; 
}

// Do action if the path specified is in the file system.
template<class F> auto doifentry(const char *path, F f) {
    for (const auto& e : ents)
        if (!strcmp(path+1, e.name.c_str()))
            return f();
    return -ENOENT;
}

// Initialize desktop shell file system.
void* fs::init(struct fuse_conn_info *conn) noexcept {
    return nullptr;
}

// Create shell file.
int fs::create(const char *path, mode_t mode, struct fuse_file_info *fi) {
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
int fs::getattr(const char *path, struct stat *stbuf) noexcept {
    // Prepare stat-buffer.
    zero(*stbuf);
    // If caller wants to check the attributes of the backslash directory.
    if (!strcmp(path, "/")) {
        stbuf->st_mode = S_IFDIR | 0755; // Directory and its permission bits.
        stbuf->st_nlink = 0;             // Number of hardlinks that points to this file that exists in the file system.
        return 0;
    } 
    // Its a file entry.
    return doifentry(path, [&]() {
        stbuf->st_mode  = S_IFREG | 0444; // File and its permission bits.
        stbuf->st_nlink = 0;              // Hard links.
        stbuf->st_size  = 0;              // uhm... size of file?
        return 0;
    });
}

// Read directory tree.
int fs::readdir(const char *path, void *buf, fuse_fill_dir_t fill, off_t offset, struct fuse_file_info *fi) {
    // Fill recursively.
    for (const auto& e : ents) {
        // Build the file entries in the buffer.
        if (fill(buf, e.name.c_str(), 0, 0) == 1) // is buffer full?
            return -ENOBUFS;
    }
    return 0;
}

#define ENTRYCHK \
    if (!exists(p)) \
        return -ENOENT; // No entry found.

// Open the desktop shell file system.
int fs::open(const char *path, struct fuse_file_info *fi) noexcept {
    return filedo(path, [](const char *p) {
        ENTRYCHK
    }, [](const char *p) {
        ENTRYCHK
    }, [](const char *p) {
        ENTRYCHK
    });
    return 0;
}

// Read file contents.
int fs::read(const char *path, char *buf, size_t size, off_t i, struct fuse_file_info *fi) noexcept {
    return doifentry(path, [&]() {
        return filedo(path, [&](const char *p) { // Display.
            // Read from display.
            dsys::read(p, buf, i, size);
            return 0;
        }, [&](const char *p) {                  // Window.
            // Read from window.
            wsys::read(p, buf, i, size);
            return 0;
        }, [](const char *p) {                   // Keyboard.
            // Read key code from keyboard.
            return kbsys::kb.get();
        });
    });
}

// Write to file. Returns exactly the number of bytes written except on error.
int fs::write(const char *path, const char *buf, size_t size, off_t i, struct fuse_file_info *fi) noexcept {
    return doifentry(path, [&]() {
        return filedo(path, [&](const char *p) { // Display.
            // Write to display named in p.
            dsys::write(buf, i, size);
            return 0;
        }, [&](const char *p) {                  // Window.
            // Write to window named in p.
            wsys::write(p, buf, i, size);
            return 0;
        }, [](const char *p) {                   // Keyboard.
            // Keyboard is read-only.
            return -EPERM; // Operation not permitted.
        });
    });
}

// Control files in shell file system.
int fs::ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) noexcept {
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
int fs::mknod(const char *path, mode_t mode, dev_t dev) {
    return create(path, mode, nullptr);
}

namespace {
    // Create standard "this" and "parent" links.
    void mklns() {
        ents.emplace_back(File("."));  // Link to current directory.
        ents.emplace_back(File("..")); // Link to parent directory.
    }
    
    // Setup and initialize displays, and make the files pointing to them.
    void mkdpys() {
        // Initialize graphical output.
        dsys::init();
        static uint i = 0; // Current index of display.
        stringstream ss;
        ss << "dpy" << i;
        ents.emplace_back(File(ss.str()));
    }
    
    // Setup mouse and make mouse files.
    void mkm() {
        // Initialize mouse.
        msys::init();
        // Make mouse files.
        static uint i = 0;
        stringstream ss;
        ss << "m" << i;
        ents.emplace_back(File(ss.str()));
    }
    
    // Setup keyboard.
    void mkkb() {
        // Initialize keyboard.
        kbsys::init();
        // Insert it into filesystem.
        static uint i = 0; // Current index of keyboard.
        stringstream ss;
        ss << "kb" << i;
        ents.emplace_back(File(ss.str()));
    }

    // Setup and make windows.
    void mkw() {
        // Initialize windows.
        wsys::init();
        // Insert it into filesystem.
        static uint i = 0; // Current index of keyboard.
        stringstream ss;
        ss << "wnd" << i;
        ents.emplace_back(File(ss.str()));
    }
}

// Cleanup shell.
void fs::cleanup() {
    // TODO: Cleanup keyboard, sound, mouse.
    dsys::deinit();
}

// Setup shell.
void fs::setup() {
    // Create standard "this" and "parent" links in the file system tree.
    mklns();

    /***********/
    /* Devices */
    /***********/

    // Connect keyboards and make keyboard files.
    //mkkb();
    // Connect mouse and make mouse files.
    //mkm();
    // Connect to displays and make them as files.
    //mkdpys();
}
