// dsh: Shell for desktops.
#include "parse.hpp"
#include "msys.hpp"
#include "log.hpp"
#include "m.hpp"
#include "run.hpp"
#include "wd.hpp"

// Server.
int main(const int argc, const char *argv[]) {
    try {
        // Parse arguments.
        parse(argc, argv);
        // Set directory to the shell filesystem.
        dsh::wd = "./dsh/";
        // Initialize window system.
        init();
        // Listen as a server and respond to window commands from clients.
        forever {
            //const auto pos = mcurpos();
        }
        return EXIT_SUCCESS;
    } catch (const int c) {
        die(c);
    } catch (const err& e) {
        error(e);
    }
    return EXIT_FAILURE;
}
