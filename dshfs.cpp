#define FUSE_USE_VERSION 26
#include <fuse.h>
#include "log.hpp"
#include "fs.hpp"

// Shell file system driver.
int main(const int   argc,   // Number of arguments.
               char *argv[]) // Pointer to the arguments itself.
{
    using namespace fs;

    // Setup file system operations.
    static fuse_operations o = {0};

    // Creation-functions:
    o.init    = init;      // Initialize the shell file system.
    o.create  = create;    // Create a file.
    o.mknod   = fs::mknod; // Make a file node.
    // I/O-functions:
    o.getattr = getattr; // Get file attributes.
    o.readdir = readdir; // Read a directory.
    o.open    = open;    // Open file
    o.read    = read;    // Read file contents.
    o.write   = write;   // Write to the contents of a file.
    // Control-functions:
    o.ioctl   = ioctl;   // Control device.

    // Start our engines!
    try {
        // Drive user-space file system.
        return fuse_main(argc, argv, &o, nullptr);
    } catch (const err& e) {
        error(e.what());
    } catch (...) {
        error("An exception from the file system was caught!");
    }

    // Cleanup the shell file system.
    try {
        cleanup();
    } catch (const err& e) {
        error(e.what());
    } catch (...) {
        error("An exception on cleanup was caught!");
    }
    return EXIT_FAILURE;
}
