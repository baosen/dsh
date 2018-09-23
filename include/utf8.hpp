#include <vector>
#include "types.hpp"

// UTF-8 character.
class utf8c : public std::vector<byte> {
public:
    // Create empty character.
    utf8c();

    // Set string of bytes containing an UTF-8 character.
    utf8c(const byte *s);

    // Set ASCII character, assuming type 'char' is ASCII.
    utf8c(const char c);

    // Set Wide character, assuming type 'char' is ASCII.
    //utf8c(const wchar_t c);

private:
    // Assign UTF-8 string of n bytes.
    void set(const byte *s, const size_t n);

    // Hide some inherited public member functions.
    using std::vector<byte>::resize;
};
