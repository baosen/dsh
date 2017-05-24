#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <string.h>
#include <errno.h>

static const char *filename = "wnd0";
static const char *contents = "Window 0";

// Initialize window file system.
static void* wnd_init(struct fuse_conn_info *conn)
{
    // Create window file on disk.
    return NULL;
}

// Get file attributes of the window.
static int wnd_getattr(const char *path, struct stat *stbuf)
{
    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/")) {
        stbuf->st_mode = S_IFDIR | 0755; // File access mode.
        stbuf->st_nlink = 2;             // Number of links that points to this file that exists in the file system.
    } else if (strcmp(path+1, filename) == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(contents);
    } else
        return -ENOENT;
    return 0;
}

// Open the window.
static int wnd_open(const char *path, struct fuse_file_info *fi)
{
    if (strcmp(path+1, filename))
        return -ENOENT;
    if ((fi->flags & O_ACCMODE) != O_RDONLY)
        return -EACCES;
    return 0;
}

// Read window's contents.
static int wnd_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
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

// Write to window. Returns exactly the number of bytes written except on error.
static int wnd_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    return 0;
}

// Control window.
static int wnd_ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data)
{
    switch (cmd) {
    default:
        break;
    }
    return -EINVAL;
}

// File system operations.
static struct fuse_operations ops = {
    .init    = wnd_init,    // Initialize.
    .getattr = wnd_getattr, // Get attributes.
    .open    = wnd_open,    // Open window to be worked upon.
    .read    = wnd_read,    // Read window's contents.
    .write   = wnd_write,   // Write to the window's contents.
    .ioctl   = wnd_ioctl,   // Control window.
};

// File system driver for windows.
int main(int argc, char *argv[])
{
    // TODO: Mount at /dsh/.

    // Drive user-space file system.
    return fuse_main(argc, argv, &ops, NULL);
}
