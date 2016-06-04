CFLAGS = -std=c++14

all: dshell

dshell: dshell.cpp log.cpp
	clang++ $^ -o $@ $(CFLAGS)
