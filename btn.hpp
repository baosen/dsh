namespace dshell {
    class Mouse {
    public:
        Mouse() {
        }
    };

    class Img {
    public:
        Img(const char* filepath) {
        }
    private:
    };

    // A classical button.
    class Btn {
    public:
        Btn(const string label) {}
    private:
        Wnd w;
    };
}
