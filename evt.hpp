#include <linux/input.h>
#include "types.hpp"

// Event-driven input using event* device file.
class Evt {
public:
    // Open event device file.
    Evt(uint i);

    // Read from event file.
    input_event rd();

    // Get event bits.
    void evbits(char*);

    // Close event device file.
    ~Evt();
private:
    int fd; // event device file descriptor.
};
