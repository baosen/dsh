#include <vector>
#include "types.hpp"

// UTF-8 character.
class UTF8char : public std::vector<byte> {
public:
    UTF8char();
    // Set string of bytes containing an UTF-8 character.
    UTF8char(const byte *s);
    // Set ASCII character, assuming type 'char' is ASCII.
    UTF8char(const char c);
    // Set Wide character, assuming type 'char' is ASCII.
    //UTF8char(const wchar_t c);
private:
    void set(const byte *s, const size_t n);

    // Hide some inherited public member functions.
    using std::vector<byte>::resize;
};
