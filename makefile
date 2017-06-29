# Set G++ as the C++ compiler.
CXX      = g++
# Set C++ compiler flags.
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra
# Set source dependencies for desktop shell.
SRC      = m.cpp wnd.cpp col.cpp pos.cpp fb.cpp scr.cpp log.cpp res.cpp ev.cpp evm.cpp msys.cpp kbsys.cpp kb.cpp wsys.cpp wd.cpp parse.cpp init.cpp mwnd.cpp rect.cpp 
# Set preprocessing definitions.
DEFS     = DEBUG
# Set the produced executable binaries.
BINS     = \
    fbtest tests dpytests \
    dsh run dshfs

# Build everything.
all: $(BINS)

# Test code.
test: $(BINS)
	./tests

# Remove built files.
clean:
	@rm -rf *.o $(BINS)

# Compile general tests.
tests: tests.cpp
	@$(CXX) $(CXXFLAGS) $< kb.cpp log.cpp -o $@

# Compile display tests.
dpytests: dpytests.cpp
	@$(CXX) $(CXXFLAGS) $< dpy.cpp log.cpp -o $@

# Displays notifications to the user.
log.o: log.cpp log.hpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Framebuffer module.
fb.o: fb.cpp scr.o log.o
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Screen module.
scr.o: scr.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Tests for the framebuffer file.
fbtest: fbtest.cpp fb.o col.o scr.o log.o
	@$(CXX) $(CXXFLAGS) $^ -o $@

dsh: dsh.cpp
	@$(CXX) $(CXXFLAGS) -D$(DEFS) $(SRC) $< -o $@

# Compile shell file system executable.
dshfs: dshfs.cpp kb.cpp kbsys.cpp fs.cpp dsys.cpp wndcmd.cpp dpycmd.cpp wsys.cpp ssys.cpp $(SRC)
	@$(CXX) $^ `pkg-config fuse --cflags --libs` -o $@

# Compile "do"-program, the beginning program that ask the user what to do.
do: do.cpp do.hpp
	@$(CXX) $(CXXFLAGS) $(SRC) $< -o $@

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all test clean
