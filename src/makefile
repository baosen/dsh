###############
# EXECUTABLES #
###############

all: dshfs.elf do.elf

# Executables.
EXECS    = dshfs.elf

# Compile shell file system executable.
dshfs.elf: dshfs.cpp fs.o log.o kb.o kbsys.o dsys.o wndcmd.o dpycmd.o wsys.o ssys.o msys.o m.o wnd.o fb.o scr.o pix.o pos.o res.o evm.o ev.o ent.o dir.o file.o kbf.o mf.o wndx.o wndy.o gn.o wndctl.o bg.o wndxc.o wndyc.o
	$(COMPILE) $^ `pkg-config fuse --cflags --libs` -o $@

# Compile "do"-program, the beginning program that ask the user what to do.
do.elf: do.cpp do.hpp
	$(COMPILE) $(SRC) $< -o $@
