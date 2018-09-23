#include "evm.hpp"
#include "fio.hpp"

// Is bit i in byte b set?
static constexpr bool bset(const char   b, // Byte to check bits.
                           const ushort i) // The ith bit to check if it is set.
{
    return !!(b & (1 << i));
}

// Check if the file opened is a mouse.
static bool ism(char b[EV_MAX]) // le bits.
{
    bool key = false, // Does the file have keys?
         rel = false; // Does it have a relative axis?

    // Check for key and relative axis.
    for (ushort i = 0; i < EV_MAX; i++) {
        // Check if bit i of the byte are set.
        if (bset(b[0], i)) {
            switch (i) {
            // Has key buttons?
            case EV_KEY:
                key = true;
                break;
            // Has relative axis?
            case EV_REL:
                rel = true;
                break;
            default:
                break;
            }
        }
    }

    // If it has both key and relative axis, then it is mouse. If some are missing, it is not a mouse.
    return key && rel;
}

// Open event mouse device file.
evm::evm() {}

// Find a "event" mouse and open it.
evm::evm(const uint i) // The ith mouse to open.
    : e(i)             // Open the ith event file.
{
    // Check if input device given has mouse capabilities.
    char b[EV_MAX];
    e.evbits(b);
    if (!ism(b))
        throw err("No mouse capabilities in this event device.");
}

// Open mouse event device file.
bool evm::open(const uint i) // The ith event mouse device file to open.
{
    return e.open(i);
}

// Close mouse event device file.
void evm::close() 
{
    e.close();
}

// Read event mouse.
input_event evm::rd() 
{
    return e.rd();
}
