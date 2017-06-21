#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define test_bit(n, p) !!(n & (1u << p))
#define PATH_TO_EVENT_FILE "/dev/input/event0"

int main() {
    int fd;
    if ((fd = open(PATH_TO_EVENT_FILE, O_RDONLY)) < 0)
        exit(EXIT_FAILURE);

    char b[256];
    int n;
    if ((n = ioctl(fd, EVIOCGBIT(0, EV_MAX), b)) < 0)
        exit(EXIT_FAILURE);

    printf("Supported event types:\n");
    for (unsigned short i = 0; i < EV_MAX; i++) {
        if (test_bit(b[0], i)) {
            printf("\t0x%02x ", i);
            switch (i) {
            case EV_SYN :
                printf("(Synch Events)\n");
                break;
            case EV_KEY :
                printf("(Keys or Buttons)\n");
                break;
            case EV_REL :
                printf("(Relative Axes)\n");
                break;
            case EV_ABS :
                printf("(Absolute Axes)\n");
                break;
            case EV_MSC :
                printf("(Miscellaneous)\n");
                break;
            case EV_LED :
                printf("(LEDs)\n");
                break;
            case EV_SND :
                printf("(Sounds)\n");
                break;
            case EV_REP :
                printf("(Repeat)\n");
                break;
            case EV_FF: case EV_FF_STATUS:
                printf("(Force Feedback)\n");
                break;
            case EV_PWR:
                printf("(Power Management)\n");
                break;
            default:
                printf("(Unknown: 0x%04hx)\n", i);
            }
        }
    }
    if (close(fd) == -1) {
        puts("Failed to close " PATH_TO_EVENT_FILE);
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/*
// Mouse button press or release.
static void key(In::Ev& ev, input_event& e) {
    switch (e.code) {
    case BTN_LEFT:    // Left mouse button.
        ev.type.m = In::MType::Left;
        ev.val.min.left = e.value;
        break;
    case BTN_RIGHT:   // Right mouse button.
        ev.type.m = In::MType::Right;
        ev.val.min.right = e.value;
        break;
    case BTN_MIDDLE:  // Middle mouse button.
        ev.type.m = In::MType::Mid;
        ev.val.min.mid = e.value;
        break;
    case BTN_SIDE:    // Side mouse button.
        ev.type.m = In::MType::Side;
        ev.val.min.side = e.value;
        break;
    case BTN_EXTRA:   // Extra mouse button?
        ev.type.m = In::MType::Extra;
        ev.val.min.extra = e.value;
        break;
    case BTN_FORWARD: // Forward button.
        ev.type.m = In::MType::Forward;
        ev.val.min.forward = e.value;
        break;
    case BTN_BACK:    // Back button (to go backwards in browser?).
        ev.type.m = In::MType::Back;
        ev.val.min.back = e.value;
        break;
    case BTN_TASK:    // Task button.
        ev.type.m = In::MType::Task;
        ev.val.min.task = e.value;
        break;
    default:
        break;
    }
}

// Mouse movement.
static void rel(In::Ev& ev, input_event& e) {
    // Mouse movements follows top-left coordinate system, where origo is at the top left of the screen and the positive y-axis points downwards.
    switch (e.code) {
    case 0: // x-axis, - left, + right.
        ev.type.m = In::MType::X;
        ev.val.min.x = e.value;
        break;
    case 1: // y-axis, - upwards, + downwards.
        ev.type.m = In::MType::Y;
        ev.val.min.y = e.value;
        break;
    case 8: // wheel scroll.
        ev.type.m = In::MType::Wheel;
        ev.val.min.wheel = e.value;
        break;
    }
}

// Handle synthetic events.
static bool syn(deque<In::Ev>& d, In::Ev& ev, const __s32 code) {
    switch (code) {
    case SYN_REPORT:
        return true;
    case SYN_DROPPED: // Oh snap!
        break; // TODO: Throw away all frames between the reports.
    }
    return false;
}

// Fill in event based on its read type.
static bool fill(deque<In::Ev>& d, input_event& e) {
    In::Ev ev;
    zero(ev);
    ev.d = In::Dev::Mouse;
    switch (e.type) {
    case EV_REL: // Relative motion.
        rel(ev, e);
        d.push_back(ev);
        return false;
    case EV_KEY: // Mouse button press and release.
        key(ev, e);
        d.push_back(ev);
        return false;
    case EV_ABS: // Absolute motion.
        // Absolute value to announce touch pad movement speed?
        return false;
    case EV_MSC: // Miscellanous?
        return false;
    case EV_SYN: // Synchronization events.
        return syn(d, ev, e.code);
    default: {
        stringstream ss;
        ss << "Unknown type:" << hex << setw(2) << e.type << endl;
        throw err(ss.str().c_str());
             }
    }
}
*/
