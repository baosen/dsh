#include "parse.hpp"
#include "log.hpp"
#include "init.hpp"
#include "wd.hpp"
#include "types.hpp"

// Shell.
int main(const int argc, const char *argv[]) {
    try {
        // Parse arguments.
        parse(argc, argv);
        // Set directory to the shell filesystem.
        dsh::wd = "./sh/";
        // Initialize window system.
        init();
        // Listen for inputs and respond to window commands from clients.
        forever {
            // TODO!
        }
        return EXIT_SUCCESS;
    } catch (const int c) {
        die(c);
    } catch (const err& e) {
        error(e);
    }
    return EXIT_FAILURE;
}
