CFLAGS = -std=c++17 -O3 -Wall -Wextra
CXX    = g++
# Set source dependencies for desktop shell.
SRC    = m.cpp wnd.cpp col.cpp pos.cpp fb.cpp scr.cpp log.cpp res.cpp ev.cpp evm.cpp msys.cpp kbsys.cpp kb.cpp wsys.cpp frect.cpp wd.cpp parse.cpp init.cpp
DEFS   = DEBUG
BINS   = test dsh run

all: $(BINS)

clean:
	@rm -rf *.o $(BINS)

# Compile tests.
test: test.cpp
	@$(CXX) $(CFLAGS) $< kb.cpp dpy.cpp log.cpp -lboost_filesystem -lboost_system -o $@

# Compile desktop shell server executable.
dsh: dsh.cpp
	@$(CXX) $(CFLAGS) -D$(DEFS) $(SRC) $< -o $@

run: run.cpp
	@$(CXX) $(CFLAGS) $(SRC) $< -o $@

.PHONY: all clean
