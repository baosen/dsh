# Set C++ compiler flags.
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra
# Set G++ as the C++ compiler.
CXX      = g++
# Set source dependencies for desktop shell.
SRC      = m.cpp wnd.cpp col.cpp pos.cpp fb.cpp scr.cpp log.cpp res.cpp ev.cpp evm.cpp msys.cpp kbsys.cpp kb.cpp wsys.cpp frect.cpp wd.cpp parse.cpp init.cpp
# Set preprocessing definitions.
DEFS     = DEBUG
# Set the produced executable binaries.
BINS     = tests dpytests dsh run dshfs

all: $(BINS)

test: $(BINS)
	./tests
clean:
	@rm -rf *.o $(BINS)

# Compile tests.
tests: tests.cpp
	@$(CXX) $(CXXFLAGS) $< kb.cpp log.cpp -o $@

# Compile display tests.
dpytests: dpytests.cpp
	@$(CXX) $(CXXFLAGS) $< dpy.cpp log.cpp -o $@

# Compile desktop shell server executable.
dsh: dsh.cpp
	@$(CXX) $(CXXFLAGS) -D$(DEFS) $(SRC) $< -o $@

dshfs: dshfs.cpp file.cpp
	@$(CXX) $^ `pkg-config fuse --cflags --libs` -o $@

run: run.cpp
	@$(CXX) $(CXXFLAGS) $(SRC) $< -o $@

.PHONY: all test clean
