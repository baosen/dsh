#include "err.hpp"
using namespace std;

// Print error code and exit.
void die(const int code) 
{
    cerr << "\033[1;31m" << "Error code: " << hex << code << "\033[0m" << endl;
    exit(code);
}

// Print error and exit.
void die(const char* e)     // Error to print out.
{
    cerr << e;
    exit(errno);
}

// Print error.
void error(const string& s) // Error to print out.
{
    cout << "\033[1;31mError:\033[0m " << s << endl;
}

// Print error.
void error(const err& e)    // Error to print out.
{
    cout << "\033[1;31mError:\033[0m " << e << endl;
}

// Print operating system error.
void syserror(const std::string& s) 
{
    error(s);  // TODO: Colorize.
    perror(0);
}

// Print warning.
void warn(const string& s) 
{
    cout << "\033[1;33mWarning:\033[0m " << s << endl;
}

// Print warning.
void warn(const char *s) 
{
    cout << "\033[1;33mWarning:\033[0m " << s << endl;
}

// Color codes: https://en.wikipedia.org/wiki/ANSI_escape_code
