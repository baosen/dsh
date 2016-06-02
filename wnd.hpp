namespace dshell {
    // TODO: Make sure windows does overlap and not collide.
    class Wnd {
    public:
        Wnd(const uint x, const uint y, const uint w, const uint h) 
            : x(x), y(y), width(w), height(h) {}

        void max() {
            oldw = width;
            oldh = height;
            width = fb.maxw();
            height = fb.maxh();
            draw();
        }

        void min() {
            draw();
        }

        void draw() {}
    private:
        uint x, y, width, height, oldw, oldh;
    };
}
