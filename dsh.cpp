// dsh: Shell for desktops.
#include "parse.hpp"
#include "init.hpp"
#include "msys.hpp"
#include "log.hpp"
#include "m.hpp"
#include "run.hpp"

#ifdef DEBUG
#   include "wd.hpp"
#endif

// Server.
int main(const int argc, const char *argv[]) {
    try {
        // Parse arguments.
        parse(argc, argv);

#ifdef DEBUG
        dsh::wd = "./dsh/";
        exit(EXIT_FAILURE);
#endif

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
