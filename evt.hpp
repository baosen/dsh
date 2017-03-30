// Event-driven input using event* device file.
class Evt {
public:
    // Open event device file.
    Evt::Evt(uint i);

    // Read from mouse event device file.
    void rd(deque<In::Evt>& d, const int fd) {
        input_event e;
        ssize_t ret;
        do {
            ret = ::read(fd, &e, sizeof e);
            if (ret == -1)   // error.
                throw errno; // todo.
            if (ret == 0)    // finished reading.
                break;
            if (fill(d, e))
                break;
        } while (ret > 0);
    }

    // Get event bits.
    void evbits(char*);

    // Close event device file.
    ~Evt();
private:
};
