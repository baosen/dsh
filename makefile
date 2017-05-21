CFLAGS = -std=c++17 -O3 -Wall -Wextra
SRC    = dsh.cpp m.cpp wnd.cpp col.cpp pos.cpp fb.cpp scr.cpp log.cpp res.cpp ev.cpp evm.cpp msys.cpp kbsys.cpp kb.cpp wsys.cpp frect.cpp wd.cpp parse.cpp init.cpp run.cpp
DEFS   = DEBUG

all:
	@g++ $(CFLAGS) -D$(DEFS) $(SRC)

clean:
	@rm -rf a.out

.PHONY: all clean
