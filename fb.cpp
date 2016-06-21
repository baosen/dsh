class Pixel {
};

void draw(const Rect& r)
{
    Slt<fb>::get()(r.x, r.y, r.w. r.h);
}
