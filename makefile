CFLAGS = -std=c++17 -O3 -Wall -Wextra
SRC    = m.cpp wnd.cpp col.cpp pos.cpp fb.cpp scr.cpp log.cpp res.cpp ev.cpp evm.cpp msys.cpp kbsys.cpp kb.cpp wsys.cpp frect.cpp wd.cpp parse.cpp init.cpp
DEFS   = DEBUG

all: dsh run

clean:
	@rm -rf *.o dsh run

dsh: dsh.cpp
	@g++ $(CFLAGS) -D$(DEFS) $(SRC) $< -o $@

run: run.cpp
	@g++ $(CFLAGS) $(SRC) $< -o $@

.PHONY: all clean
