# TODO: Set the number of parallell jobs to be run to be equal to the number of CPU cores.
#CPUS      ?= $(shell sysctl -n hw.ncpu || echo 1)
#MAKEFLAGS += --jobs=$(CPUS)

# Set C++ compiler.
CXX      = g++
# Set C++ compiler flags.
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -g
# Compile command.
COMPILE  = @$(CXX) $(CXXFLAGS)
# FUSE libraries.
FUSELIBS = `pkg-config fuse --cflags --libs`

# Tests.
TESTS    = mtest.elf fbtest.elf evmtest.elf kbsystest.elf msystest.elf dpytests.elf wtest.elf kbtest.elf utf8test.elf fsktest.elf fsmtest.elf enttest.elf gntest.elf wndfstest.elf wsystest.elf

# Executables.
EXECS    = dshfs.elf

# Set the produced executable binaries.
BINS     = $(TESTS) $(EXECS)

##########
# BUILDS #
##########

.PHONY: all release test clean

# Build everything.
all: $(BINS)

release: $(BINS)

# Remove built files.
clean:
	@rm -rf *.o $(BINS)

###########
# OBJECTS #
###########

# Displays notifications to the user.
log.o: log.cpp log.hpp
	$(COMPILE) -c $< -o $@

# Framebuffer module.
fb.o: fb.cpp scr.o log.o
	$(COMPILE) -c $< -o $@

# Screen module.
scr.o: scr.cpp
	$(COMPILE) -c $< -o $@

# File system.
fs.o: fs.cpp fs.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# File system entries.
ent.o: ent.cpp ent.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# File entries.
file.o: file.cpp file.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Directory entries.
dir.o: dir.cpp dir.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Keyboard file.
kbf.o: kbf.cpp kbf.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Mouse file.
mf.o: mf.cpp mf.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window directory.
wndd.o: wndd.cpp wndd.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window x coordinate file.
wndx.o: wndx.cpp wndy.hpp gn.o
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window y coordinate file.
wndy.o: wndy.cpp wndy.hpp gn.o
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window x ASCII coordinate file.
wndxc.o: wndxc.cpp wndxc.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window y ASCII coordinate file.
wndyc.o: wndyc.cpp wndyc.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window ctl.
wndctl.o: wndctl.cpp wndctl.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

%.o: %.cpp
	$(COMPILE) -c $< -o $@

############
#  TESTS   #
############

# Tests for the framebuffer file.
fbtest.elf: fbtest.cpp fb.o pix.o scr.o log.o keywait.o
	$(COMPILE) $^ -o $@

# Tests for the window files.
wtest.elf: wtest.cpp fb.o pix.o scr.o log.o pos.o wnd.o res.o keywait.o m.o
	$(COMPILE) $^ -o $@

# Tests for the hacky mouse file.
mtest.elf: mtest.cpp m.o log.o
	$(COMPILE) $^ -o $@

# Tests for the event mouse device file.
evmtest.elf: evmtest.cpp evm.o log.o ev.o
	$(COMPILE) $^ -o $@

# Tests for the mouse subsystem.
msystest.elf: msystest.cpp msys.o evm.o ev.o m.o log.o
	$(COMPILE) $^ -o $@

# Tests for the window subsystem.
wsystest.elf: wsystest.cpp wsys.o keywait.o wnd.o pos.o res.o fb.o scr.o pix.o log.o bg.o
	$(COMPILE) $^ -o $@

# Tests for the keyboard subsystem.
kbsystest.elf: kbsystest.cpp kbsys.o kb.o kbc.o evm.o ev.o m.o log.o locale.o
	$(COMPILE) $^ -o $@ -lpthread

# Keyboard file tests.
fsktest.elf: fsktest.cpp kbc.o locale.o
	$(COMPILE) $^ -o $@

# Window file tests.
wndfstest.elf: wndfstest.cpp log.o pos.o keywait.o
	$(COMPILE) $^ $(FUSELIBS) -o $@

# Mouse file tests.
fsmtest.elf: fsmtest.cpp
	$(COMPILE) $^ -o $@

enttest.elf: enttest.cpp ent.o dir.o file.o log.o
	$(COMPILE) $^ $(FUSELIBS) -o $@

gntest.elf: gntest.cpp gn.o
	$(COMPILE) $^ -o $@

# Tests for keyboard.
kbtest.elf: kbtest.cpp kb.o kbc.o utf8.o
	$(COMPILE) $^ -o $@

# Tests for UTF-8 characters.
utf8test.elf: utf8test.cpp utf8.o
	$(COMPILE) $^ -o $@

# Compile display tests.
dpytests.elf: dpytests.cpp
	$(COMPILE) $< dpy.cpp log.cpp -o $@


###############
# EXECUTABLES #
###############

# Compile shell file system executable.
dshfs.elf: dshfs.cpp fs.o log.o kb.o kbsys.o dsys.o wndcmd.o dpycmd.o wsys.o ssys.o msys.o m.o wnd.o fb.o scr.o pix.o pos.o res.o evm.o ev.o ent.o dir.o file.o kbf.o mf.o wndx.o wndy.o gn.o wndctl.o bg.o wndxc.o wndyc.o
	$(COMPILE) $^ `pkg-config fuse --cflags --libs` -o $@

# Compile "do"-program, the beginning program that ask the user what to do.
do.elf: do.cpp do.hpp
	$(COMPILE) $(SRC) $< -o $@
