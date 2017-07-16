# Set the number of parallell jobs to be run to be equal to the number of CPU cores.
#CPUS      ?= $(shell sysctl -n hw.ncpu || echo 1)
#MAKEFLAGS += --jobs=$(CPUS)

# Set G++ as the C++ compiler.
CXX      = g++
# Set C++ compiler flags.
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra
# Compile command.
COMPILE  = @$(CXX) $(CXXFLAGS)
# Set source dependencies for desktop shell.
SRC      = m.cpp wnd.cpp pix.cpp pos.cpp fb.cpp scr.cpp log.cpp res.cpp ev.cpp evm.cpp msys.cpp kbsys.cpp kb.cpp wsys.cpp wd.cpp parse.cpp init.cpp mwnd.cpp rect.cpp 
# Tests.
TESTS    = mtest fbtest evmtest kbsystest msystest dpytests wtest kbtest utf8test fsktest fsmtest
# Executables.
EXECS    = dsh dshfs
# Set the produced executable binaries.
BINS     = $(TESTS) $(EXECS)

# Build everything.
all: $(BINS)

# Remove built files.
clean:
	@rm -rf *.o $(BINS)

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
	$(COMPILE) -c $< -o $@

# Tests for the framebuffer file.
fbtest: fbtest.cpp fb.o pix.o scr.o log.o keywait.o
	$(COMPILE) $^ -o $@

# Tests for the window files.
wtest: wtest.cpp fb.o pix.o scr.o log.o pos.o rect.o res.o keywait.o m.o
	$(COMPILE) $^ -o $@

recttest: recttest.cpp rect.o fb.o pix.o scr.o log.o pos.o res.o keywait.o
	$(COMPILE) $^ -o $@

# Tests for the hacky mouse file.
mtest: mtest.cpp m.o log.o
	$(COMPILE) $^ -o $@

# Tests for the event mouse device file.
evmtest: evmtest.cpp evm.o log.o ev.o
	$(COMPILE) $^ -o $@

# Tests for the mouse subsystem.
msystest: msystest.cpp msys.o evm.o ev.o m.o log.o
	$(COMPILE) $^ -o $@

# Tests for the keyboard subsystem.
kbsystest: kbsystest.cpp kbsys.o kb.o kbc.o evm.o ev.o m.o log.o locale.o
	$(COMPILE) $^ -o $@ -lpthread

# Keyboard file tests.
fsktest: fsktest.cpp kbc.o locale.o
	$(COMPILE) $^ -o $@

# Mouse file tests.
fsmtest: fsmtest.cpp
	$(COMPILE) $^ -o $@

# Tests for keyboard.
kbtest: kbtest.cpp kb.o kbc.o utf8.o
	$(COMPILE) $^ -o $@

# Tests for UTF-8 characters.
utf8test: utf8test.cpp utf8.o
	$(COMPILE) $^ -o $@

# The shell running on top of the filesystem in userspace.
dsh: dsh.cpp
	$(COMPILE) $(SRC) $< -o $@ -lpthread

# File system.
fs.o: fs.cpp
	$(COMPILE) -c $^ `pkg-config fuse --cflags --libs` -o $@

# Compile shell file system executable.
dshfs: dshfs.cpp fs.o log.o kb.o kbsys.o dsys.o wndcmd.o dpycmd.o wsys.o ssys.o msys.o m.o wnd.o fb.o scr.o pix.o rect.o pos.o res.o evm.o ev.o
	$(COMPILE) $^ `pkg-config fuse --cflags --libs` -o $@

# Compile "do"-program, the beginning program that ask the user what to do.
do: do.cpp do.hpp
	$(COMPILE) $(SRC) $< -o $@

%.o: %.cpp
	$(COMPILE) -c $< -o $@

.PHONY: all test clean
