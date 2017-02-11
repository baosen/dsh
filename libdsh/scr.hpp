class Ptr;

// Computer screen.
class Scr {
    int fd;
    uint w,                      // Width.
         h,                      // Height.
         bpp,                    // Bits per pixel.
         roff, goff, boff, aoff, // Offset to pixel in bits. Bitshift to reach it.
         rl, gl, bl, al;         // Length in bits.
    size_t size;
    friend class Ptr;
    friend class Fb;
public:
    typedef fb_var_screeninfo varinfo;
    typedef fb_fix_screeninfo fixinfo;

    Scr();
    ~Scr();

    varinfo vinfo();
    fixinfo finfo();

    Ptr map();
};

