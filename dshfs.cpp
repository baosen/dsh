#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static const char *filename = "dsh";
static const char *contents = "Desktop shell.";

// Initialize desktop shell file system.
static void *dsh_init(struct fuse_conn_info *conn)
{
    return NULL;
}

// Get file attributes of the desktop shell.
static int dsh_getattr(const char *path, struct stat *stbuf)
{
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755; // Permission bits.
        stbuf->st_nlink = 2;             // Number of hardlinks that points to this file that exists in the file system.
    } else if (strcmp(path+1, filename) == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(contents);
    } else
        return -ENOENT;
    return 0;
}

// Open the desktop shell file system.
static int dsh_open(const char *path, struct fuse_file_info *fi)
{
    if (strcmp(path+1, filename))
        return -ENOENT;
    if ((fi->flags & O_ACCMODE) != O_RDONLY)
        return -EACCES;
    return 0;
}

// Read file contents.
static int dsh_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
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
static int dsh_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    return 0;
}

// Control display.
static int dsh_ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data)
{
    // TODO: Check path for what kind of file is opened.
    puts(path);
    // Either:
    // -dpy*: display.
    // -wnd*: window.
    // -rect*: rectangle.
    switch (cmd) {
    default:
        break;
    }
    return -EINVAL;
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

    // Drive user-space file system.
    return fuse_main(argc, argv, &ops, NULL);
}
