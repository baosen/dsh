#pragma once
#include <string>
#include "fio.hpp"
#include "rect.hpp"
#include "pos.hpp"

// File rectangle.
// The rectangle is stored as a file in the file system.
class Frect : public Rect {
public:
    Frect(const std::string& name);
    Frect(const char *name);
    Frect(const Pos& p);
    Frect();

    // Fill rectangle with colour.
    virtual void   fill(const Col& c) const;

    // Returns the index to its position in the rectangle.
    virtual uint   i()    const;
    // Returns the rectangle area size.
    virtual size_t size() const;

    // Resize rectangle image.
    virtual void resize(const uint w, const uint h);

    virtual ~Frect();
private:
    int         fd; // File descriptor.
    std::string name;
};
