#include <linux/input.h>

// Event-driven input using event* device file.
class Evt {
public:
    // Open event device file.
    Evt::Evt(uint i);

    // Read from event file.
    input_event Evt::rd();

    // Get event bits.
    void evbits(char*);

    // Close event device file.
    ~Evt();
private:
    int fd; // event device file descriptor.
};
