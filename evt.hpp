// Event file.
class Evt {
public:
    // Open event file.
 I  Evt(const char *path) {
        stringstream ss;
        // Event-driven input using event* device file.
        if (strstr(path, "event") && ((fd = ::open(path, O_RDONLY)) != -1))
            return;
        ss << "Cannot open " << path << ": " << strerror(errno);
        error(ss.str());
        throw err("Failed to open input device!");
    }

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

    ~Evt() {
        stringstream ss;
        if (::close(fd) == -1) {
            ss << "Cannot close " << path << ": " << strerror(errno);
            die(ss.str().c_str());
        }
    }
private:
};
