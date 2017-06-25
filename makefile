# Set G++ as the C++ compiler.
CXX      = g++
# Set C++ compiler flags.
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra
# Set source dependencies for desktop shell.
SRC      = m.cpp wnd.cpp col.cpp pos.cpp fb.cpp scr.cpp log.cpp res.cpp ev.cpp evm.cpp msys.cpp kbsys.cpp kb.cpp wsys.cpp wd.cpp parse.cpp init.cpp mwnd.cpp rect.cpp 
# Set preprocessing definitions.
DEFS     = DEBUG
# Set the produced executable binaries.
BINS     = tests dpytests dsh run dshfs

all: $(BINS)

test: $(BINS)
	./tests
clean:
	@rm -rf *.o $(BINS)

# Compile general tests.
tests: tests.cpp
	@$(CXX) $(CXXFLAGS) $< kb.cpp log.cpp -o $@

# Compile display tests.
dpytests: dpytests.cpp
	@$(CXX) $(CXXFLAGS) $< dpy.cpp log.cpp -o $@

dsh: dsh.cpp
	@$(CXX) $(CXXFLAGS) -D$(DEFS) $(SRC) $< -o $@

# Compile shell file system executable.
dshfs: dshfs.cpp kb.cpp kbsys.cpp fs.cpp dsys.cpp wndcmd.cpp dpycmd.cpp wsys.cpp ssys.cpp $(SRC)
	@$(CXX) $^ `pkg-config fuse --cflags --libs` -o $@

# Compile "do"-program, the beginning program that ask the user what to do.
do: do.cpp do.hpp
	@$(CXX) $(CXXFLAGS) $(SRC) $< -o $@

.PHONY: all test clean
