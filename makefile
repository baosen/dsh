# Set G++ as the C++ compiler.
CXX      = g++
# Set C++ compiler flags.
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra
# Compile command.
COMPILE = @$(CXX) $(CXXFLAGS)
# Set source dependencies for desktop shell.
SRC      = m.cpp wnd.cpp col.cpp pos.cpp fb.cpp scr.cpp log.cpp res.cpp ev.cpp evm.cpp msys.cpp kbsys.cpp kb.cpp wsys.cpp wd.cpp parse.cpp init.cpp mwnd.cpp rect.cpp 
# Set preprocessing definitions.
DEFS     = DEBUG
# Set the produced executable binaries.
BINS     = \
    mtest fbtest tests dpytests \
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
	$(COMPILE) $< kb.cpp log.cpp -o $@

# Compile display tests.
dpytests: dpytests.cpp
	$(COMPILE) $< dpy.cpp log.cpp -o $@

# Displays notifications to the user.
log.o: log.cpp log.hpp
	$(COMPILE) -c $< -o $@

# Framebuffer module.
fb.o: fb.cpp scr.o log.o
	$(COMPILE) -c $< -o $@

# Screen module.
scr.o: scr.cpp
	$(COMPILE) -c $< -o $@ -DDEBUG

# Tests for the framebuffer file.
fbtest: fbtest.cpp fb.o col.o scr.o log.o
	$(COMPILE) $^ -o $@

# Tests for the hacky mouse file.
mtest: mtest.cpp m.o log.o
	$(COMPILE) $^ -o $@

dsh: dsh.cpp
	$(COMPILE) -D$(DEFS) $(SRC) $< -o $@

# Compile shell file system executable.
dshfs: dshfs.cpp kb.cpp kbsys.cpp fs.cpp dsys.cpp wndcmd.cpp dpycmd.cpp wsys.cpp ssys.cpp $(SRC)
	@$(CXX) $^ `pkg-config fuse --cflags --libs` -o $@

# Compile "do"-program, the beginning program that ask the user what to do.
do: do.cpp do.hpp
	$(COMPILE) $(SRC) $< -o $@

%.o: %.cpp
	$(COMPILE) -c $< -o $@

.PHONY: all test clean
