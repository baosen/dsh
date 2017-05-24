#define FUSE_USE_VERSION 26
#include <cassert>
#include <string>
#include <memory>
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
using namespace std;

// File parent with childs.
class File {
public:
    // Create file tree node.
    File(const char* name) : name(name), childs(nullptr), n(0) {}

    // Create file tree node with n childs.
    File(const char* name, const uint n) : name(name), n(n) {
        if (n)
            childs = (File*)new char[n*sizeof(File)];
        else
            childs = nullptr;
    }

    // Destroy file and its childs.
    ~File() {
        // TODO: Free tree.
    }

    const char *name;   // Pointer to the name of the file as a C-string.
    File       *childs; // Children nodes.
    uint        n;      // Number of children.
};

namespace {
    File *root;
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
static int dsh_getattr(const char *path, struct stat *stbuf) noexcept
{
    memset(stbuf, 0, sizeof(struct stat));
    if (!strcmp(path, "/")) {
        stbuf->st_mode = S_IFDIR | 0755; // Directory.
        stbuf->st_nlink = 2;             // Number of hardlinks that points to this file that exists in the file system.
    } else if (!strcmp(path+1, filename)) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(contents);
        stbuf->st_size = strlen(contents);
    } else {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 0;
        stbuf->st_size = 0;
        //return -ENOENT;
    }
    return 0;
}

// Read directory.
static int dsh_readdir(const char *path, void *buf, fuse_fill_dir_t fill, off_t offset, struct fuse_file_info *fi) 
{
    fill(buf, ".", NULL, 0);  // Current directory.
    fill(buf, "..", NULL, 0); // Parent directory.
    // TODO: Build tree structure containing created files.
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

    // Initialize file tree.
    // TODO: Wrap exception.
    root = new File("/", 2);
    new (root->childs) File(".");
    new (root->childs+1) File("..");

    // Drive user-space file system.
    const auto ret = fuse_main(argc, argv, &ops, nullptr);
    delete root;
    return ret;
}
