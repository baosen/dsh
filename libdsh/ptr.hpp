class Ptr {
    size_t size;
    char* fb;
public:
    Ptr() {}

    Ptr(Scr& s) {
        size = s.finfo().smem_len;
        fb = scast<char*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, s.fd, 0));
    }

    char& operator[](const uint i) {
        return rcast<char*>(fb)[i];
    }

    u32& i32(const uint i) {
        return *(rcast<u32*>(fb)+i);
    }

    Ptr(const Ptr&) {
    }

    Ptr(const Ptr&&) {
    }

    Ptr operator=(const Ptr& p) {
    }

    ~Ptr() {
        if (munmap(fb, size) == -1) {
            perror("Error");
            exit(errno);
        }
    }
};
