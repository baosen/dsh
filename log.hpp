#include <iostream>
#include "err.hpp"

// Print message and exist.
void die(const int);
void die(const char*);

void error(const std::string&);
void error(const err&);
void syserror(const std::string& s);

// Warn user about something happened.
void warn(const string& s);
void warn(const char*);
