#define FUSE_USE_VERSION 26
#include <cassert>
#include <string>
#include <memory>
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "zero.hpp"
#include "types.hpp"
#include "file.hpp"
using namespace std;

namespace {
    File *ents; // File entries.
    uint nents; // Number of file entries.
}

static const char *filename = "dsh";
static const char *contents = "Desktop shell.";

// Do correct file operation according to the file type.
template<class F, class W>
int filedo(const char *path, F df, W wf) {
    // Check path for what kind of file is opened.
    const char *bs = nullptr;
    for (const char *p = path; *p; ++p)
        if (*p == '/')
            bs = p; // Set position of backslash.
    const char *s;
    if ((s = strstr(bs, "dpy")))      // Is a display?
        df(s);
    else if ((s = strstr(bs, "wnd"))) // Is a window?
        wf(s);
    else
        return -EINVAL; // Unknown file.
    return 0; // Ok!
}

// Initialize desktop shell file system.
static void *dsh_init(struct fuse_conn_info *conn) noexcept
{
    return NULL;
}

// Get file attributes of the desktop shell.
static int dsh_getattr(const char *path, struct stat *buf) noexcept
{
    zero(*buf);
    if (!strcmp(path, "/")) {
        buf->st_mode = S_IFDIR | 0755; // Directory.
        buf->st_nlink = 2;             // Number of hardlinks that points to this file that exists in the file system.
    } else if (!strcmp(path+1, filename)) {
        buf->st_mode = S_IFREG | 0444;
        buf->st_nlink = 1;
        buf->st_size = strlen(contents);
    } else {
        buf->st_mode = S_IFREG | 0444;
        buf->st_nlink = 0;
        buf->st_size = 0;
        //return -ENOENT;
    }
    return 0;
}

namespace {
    void*           buffer;
    fuse_fill_dir_t filler;
}

// Fill buffer with file entries.
static void fillbuf(File* cur) 
{
    for (uint i = 0; i < nents; ++i)
        filler(buffer, ents[i].name, nullptr, 0);
}

// Read directory.
static int dsh_readdir(const char *path, void *buf, fuse_fill_dir_t fill, off_t offset, struct fuse_file_info *fi) 
{
    // Initialize.
    buffer = buf;
    filler = fill;
    // Fill recursively.
    fillbuf(ents);
    return 0;
}

// Open the desktop shell file system.
static int dsh_open(const char *path, struct fuse_file_info *fi) noexcept
{
    filedo(path, [](const char *p) {
        puts("Display!");
    }, [](const char *p) {
        puts("Window!");
    });

    if (strcmp(path+1, filename))
        return -ENOENT;
    if ((fi->flags & O_ACCMODE) != O_RDONLY)
        return -EACCES;
    return 0;
}

// Read file contents.
static int dsh_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) noexcept
{
    // TODO: Check what kind of file is read.
    size_t len;
    if (strcmp(path+1, filename))
        return -ENOENT;
    len = strlen(contents);
    if (offset < len) {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, contents + offset, size);
    } else
        size = 0;
    return size;
}

// Write to display. Returns exactly the number of bytes written except on error.
static int dsh_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) noexcept
{
    filedo(path, [](const char *p) {
    }, [](const char *p) {
    });
    return 0;
}

// Control files in shell file system.
static int dsh_ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) noexcept
{
    filedo(path, [](const char *p) {
    }, [](const char *p) {
    });

    switch (cmd) {
    default:
        break;
    }
    return -EINVAL;
}

// Create file.
static int dsh_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    return filedo(path, [](const char *p) {
    }, [](const char *p) {
    });
}

// File system driver for displays.
int main(int argc, char *argv[])
{
    // File system operations.
    static fuse_operations ops = {0};
    ops.init    = dsh_init;    // Initialize.
    ops.getattr = dsh_getattr; // Get attributes.
    ops.open    = dsh_open;    // Open display to be worked upon.
    ops.read    = dsh_read;    // Read display's contents.
    ops.write   = dsh_write;   // Write to the display's contents.
    ops.ioctl   = dsh_ioctl;   // Control display.
    ops.create  = dsh_create;  // Create file.
    ops.readdir = dsh_readdir; // Read directory.

    auto ret = EXIT_FAILURE;
    try {
        // Create file tree.
        nents = 2;
        ents  = fnew(2);
        new (ents)   File(".");
        new (ents+1) File("..");
        // Drive user-space file system.
        const auto ret = fuse_main(argc, argv, &ops, nullptr);
        delete[] rcast<char*>(ents);
    } catch (...) {
        return EXIT_FAILURE;
    }
    return ret;
}
