CFLAGS = -std=c++17 -O3 -Wall -Wextra
SRC    = btn.cpp col.cpp drm.cpp dsh.cpp fb.cpp ft.cpp kb.cpp log.cpp mouse.cpp open.cpp path.cpp pos.cpp rect.cpp res.cpp scr.cpp wnd.cpp

all:
	g++ $(CFLAGS) mrd.cpp in.cpp mouse.cpp log.cpp

clean:

.PHONY: all clean
