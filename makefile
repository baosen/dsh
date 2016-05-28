CFLAGS = -std=c++14

all: deskshell

deskshell: deskshell.cpp
	g++ $< -o $@ $(CFLAGS)
