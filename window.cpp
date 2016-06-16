class Resolution {
public:
    Resolution(const unsigned int width, const unsigned int height) {}
private:
};

class Position : public Vector<1, 2> {
public:
    Position(const unsigned int x, const unsigned int y)
            : Vector(x, y) {}
private:
};

class Window {
public:
    Window(Position placement_position, Resolution window_resolution) {
        draw();
    }
    void maximize_window();
    void minimize_window();
private:
};
