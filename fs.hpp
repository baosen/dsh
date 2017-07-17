#pragma once
#include <fuse.h>

// FUSE file operations.
namespace fs {
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

    // Read file contents. Returns number of elements read.
    int read(const char            *path, 
             char                  *buf,   // Acts as a void*.
             const size_t           n, 
             const off_t            offset, 
             struct fuse_file_info *fi) 
             noexcept;

    // Write to file. Returns exactly the number of elements written except on error.
    int write(const char            *path, 
              const char            *buf,   // Act as a void*.
              const size_t           n, 
              const off_t            offset, 
              struct fuse_file_info *fi) 
              noexcept;

    // Control files in shell file system.
    int ioctl(const char *path, int cmd, void *arg, struct fuse_file_info *fi, unsigned int flags, void *data) noexcept;

    // Make shell file node. Gets called for creation of all non-directory, non-symbolic link nodes.
    int mknod(const char *path, mode_t mode, dev_t dev) noexcept;

    // Setup.
    void setup();

    // Cleanup
    void cleanup();
}
