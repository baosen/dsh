# Set compiler flags.
CFLAGS   = -std=c11 -O3 -Wall -Wextra
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra
# Set GCC as the C compiler.
CC	     = gcc
# Set G++ as the C++ compiler.
CXX      = g++
# Set source dependencies for desktop shell.
SRC      = m.cpp wnd.cpp col.cpp pos.cpp fb.cpp scr.cpp log.cpp res.cpp ev.cpp evm.cpp msys.cpp kbsys.cpp kb.cpp wsys.cpp frect.cpp wd.cpp parse.cpp init.cpp
# Set preprocessing definitions.
DEFS     = DEBUG
# Set the produced executable binaries.
BINS     = test dsh run dpyfs

all: $(BINS)

clean:
	@rm -rf *.o $(BINS)

# Compile tests.
test: test.cpp
	@$(CXX) $(CXXFLAGS) $< kb.cpp dpy.cpp log.cpp -lboost_filesystem -lboost_system -o $@

# Compile desktop shell server executable.
dsh: dsh.cpp
	@$(CXX) $(CXXFLAGS) -D$(DEFS) $(SRC) $< -o $@

dpyfs: dpyfs.c
	@$(CC) $< `pkg-config fuse --cflags --libs` -o $@

run: run.cpp
	@$(CXX) $(CXXFLAGS) $(SRC) $< -o $@

.PHONY: all clean
