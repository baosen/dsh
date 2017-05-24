#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <string.h>
#include <errno.h>

static const char *filename = "dpy0";
static const char *contents = "Display 0";

// Initialize display.
static void *dpy_init(struct fuse_conn_info *conn)
{
    return NULL;
}

// Get file attributes of the display.
static int dpy_getattr(const char *path, struct stat *stbuf)
{
    int res = 0;
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755; // File access mode.
        stbuf->st_nlink = 2;             // Number of links that points to this file that exists in the file system.
    } else if (strcmp(path+1, filename) == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(contents);
    } else
        res = -ENOENT;
    return res;
}

// Open the display.
static int dpy_open(const char *path, struct fuse_file_info *fi)
{
    if (strcmp(path+1, filename))
        return -ENOENT;
    if ((fi->flags & O_ACCMODE) != O_RDONLY)
        return -EACCES;
    return 0;
}

// Read display's contents.
static int dpy_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
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
static int dpy_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    return 0;
}

// Control display.
static int dpy_ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data)
{
    switch (cmd) {
    default:
        break;
    }
    return -EINVAL;
}

// File system operations.
static struct fuse_operations ops = {
    .init    = dpy_init,    // Initialize.
    .getattr = dpy_getattr, // Get attributes.
    .open    = dpy_open,    // Open display to be worked upon.
    .read    = dpy_read,    // Read display's contents.
    .write   = dpy_write,   // Write to the display's contents.
    .ioctl   = dpy_ioctl,   // Control display.
};

// File system driver for displays.
int main(int argc, char *argv[])
{
    // TODO: Mount at /dsh/.

    // Drive user-space file system.
    return fuse_main(argc, argv, &ops, NULL);
}
