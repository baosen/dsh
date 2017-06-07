#pragma once
#include <fuse.h>

namespace fs {
    /* FUSE file operations */
    // Initialize desktop shell file system.
    void *init(struct fuse_conn_info *conn) noexcept;
    // Create shell file.
    int create(const char *path, mode_t mode, struct fuse_file_info *fi) noexcept;
    // Get file attributes of a file in the shell file system.
    int getattr(const char *path, struct stat *buf) noexcept;
    // Read directory tree.
    int readdir(const char *path, void *buf, fuse_fill_dir_t fill, off_t offset, struct fuse_file_info *fi) noexcept;
    // Open the desktop shell file system.
    int open(const char *path, struct fuse_file_info *fi) noexcept;
    // Read file contents.
    int read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) noexcept;
    // Write to display. Returns exactly the number of bytes written except on error.
    int write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) noexcept;
    // Control files in shell file system.
    int ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) noexcept;
    // Make shell file node. Gets called for creation of all non-directory, non-symbolic link nodes.
    int mknod(const char *path, mode_t mode, dev_t dev) noexcept;

    // Setup.
    void setup();
    // Cleanup
    void cleanup();
}
