#include <linux/input.h>
#include "types.hpp"

// Event-driven input using event* device file.
class Ev {
public:
    // Open event device file.
    Ev(uint i);

    // Read from event file.
    input_event rd();

    // Get event bits.
    void evbits(char*);

    // Close event device file.
    ~Ev();
private:
    int fd; // event device file descriptor.
};
