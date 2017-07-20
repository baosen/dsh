#include "wndf.hpp"
#include "wsys.hpp"

wndf::wndf(const std::string name)
    : file(name)
{}

int wndf::read(char         *buf, 
               const off_t  i, 
               const size_t nbytes)
{
}

int wndf::write(const char  *buf,    // Buffer to write from.
                const off_t  i,      // Index.
                const size_t nbytes) // Number of bytes to write.
{
}
