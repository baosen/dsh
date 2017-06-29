#define FUSE_USE_VERSION 26
#include <fuse.h>
#include "log.hpp"
#include "fs.hpp"

// Shell file system driver.
int main(int argc, char *argv[]) {
    using namespace fs;

    // Setup file system operations.
    static fuse_operations ops = {0};

    // Creation-functions:
    ops.init    = init;      // Initialize file system.
    ops.create  = create;    // Create file.
    ops.mknod   = fs::mknod; // Make file node.
    // I/O-functions:
    ops.getattr = getattr; // Get attributes.
    ops.readdir = readdir; // Read directory.
    ops.open    = open;    // Open display to be worked upon.
    ops.read    = read;    // Read display's contents.
    ops.write   = write;   // Write to the display's contents.
    // Control-functions:
    ops.ioctl   = ioctl;   // Control display.

    // Start our engines!
    int ret = EXIT_FAILURE;
    try {
        // Setup shell.
        setup();
        // Drive user-space file system.
        ret = fuse_main(argc, argv, &ops, nullptr);
    } catch (...) {
        // TODO: Show more informed error messages.
        error("An exception was caught!");
        ret = EXIT_FAILURE;
    }
    try {
        // Cleanup the shell file system.
        cleanup();
    } catch (...) {
        // TODO: Show more informed error messages.
        error("An exception caught!");
        ret = EXIT_FAILURE;
    }
    return ret;
}
