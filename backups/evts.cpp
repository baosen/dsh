#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define test_bit(n, p) !!(n & (1u << p))

int main() {
    int fd;
    if ((fd = open("/dev/input/event0", O_RDONLY)) < 0) {
        exit(1);
    }
    char b[256];
    int n;
    if ((n = ioctl(fd, EVIOCGBIT(0, EV_MAX), b)) < 0) {
        exit(1);
    }

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
    close(fd);
}
