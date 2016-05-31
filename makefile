CFLAGS = -std=c++14

all: dshell

dshell: dshell.cpp log.cpp
	g++ $^ -o $@ $(CFLAGS)
