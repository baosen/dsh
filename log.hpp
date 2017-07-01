#include <iostream>
#include "err.hpp"

void die(const int);
void die(const char*);
void error(const std::string&);
void error(const err&);
void syserror(const std::string& s);
void warn(const char*);
