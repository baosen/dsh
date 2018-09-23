############
#  TESTS   #
############

all: \
	$(TESTDIR)/mtest.elf \
	$(TESTDIR)/fbtest.elf \
	$(TESTDIR)/evmtest.elf \
	$(TESTDIR)/kbsystest.elf \
	$(TESTDIR)/msystest.elf \
	$(TESTDIR)/dpytests.elf \
	$(TESTDIR)/wtest.elf \
	$(TESTDIR)/kbtest.elf \
	$(TESTDIR)/utf8test.elf \
	$(TESTDIR)/fsktest.elf \
	$(TESTDIR)/fsmtest.elf \
	$(TESTDIR)/enttest.elf \
	$(TESTDIR)/gntest.elf \
	$(TESTDIR)/wndfstest.elf \
	$(TESTDIR)/wsystest.elf

# Tests for the framebuffer file.
$(TESTDIR)/fbtest.elf: fbtest.cpp $(OBJDIR)/fb.o $(OBJDIR)/pix.o $(OBJDIR)/scr.o $(OBJDIR)/log.o $(OBJDIR)/keywait.o
	$(COMPILE) $^ -o $@

# Tests for the window files.
$(TESTDIR)/wtest.elf: wtest.cpp $(OBJDIR)/fb.o $(OBJDIR)/pix.o $(OBJDIR)/scr.o $(OBJDIR)/log.o $(OBJDIR)/pos.o $(OBJDIR)/wnd.o $(OBJDIR)/res.o $(OBJDIR)/keywait.o $(OBJDIR)/m.o
	$(COMPILE) $^ -o $@

# Tests for the hacky mouse file.
$(TESTDIR)/mtest.elf: mtest.cpp $(OBJDIR)/m.o $(OBJDIR)/log.o
	$(COMPILE) $^ -o $@

# Tests for the event mouse device file.
$(TESTDIR)/evmtest.elf: evmtest.cpp $(OBJDIR)/evm.o $(OBJDIR)/log.o $(OBJDIR)/ev.o
	$(COMPILE) $^ -o $@

# Tests for the mouse subsystem.
$(TESTDIR)/msystest.elf: msystest.cpp $(OBJDIR)/msys.o $(OBJDIR)/evm.o $(OBJDIR)/ev.o $(OBJDIR)/m.o $(OBJDIR)/log.o
	$(COMPILE) $^ -o $@

# Tests for the window subsystem.
$(TESTDIR)/wsystest.elf: wsystest.cpp $(OBJDIR)/wsys.o $(OBJDIR)/keywait.o $(OBJDIR)/wnd.o $(OBJDIR)/pos.o $(OBJDIR)/res.o $(OBJDIR)/fb.o $(OBJDIR)/scr.o $(OBJDIR)/pix.o $(OBJDIR)/log.o $(OBJDIR)/bg.o
	$(COMPILE) $^ -o $@

# Tests for the keyboard subsystem.
$(TESTDIR)/kbsystest.elf: kbsystest.cpp $(OBJDIR)/kbsys.o $(OBJDIR)/kb.o $(OBJDIR)/kbc.o $(OBJDIR)/evm.o $(OBJDIR)/ev.o $(OBJDIR)/m.o $(OBJDIR)/log.o $(OBJDIR)/locale.o
	$(COMPILE) $^ -o $@ -lpthread

# Keyboard file tests.
$(TESTDIR)/fsktest.elf: fsktest.cpp $(OBJDIR)/kbc.o $(OBJDIR)/locale.o
	$(COMPILE) $^ -o $@

# Window file tests.
$(TESTDIR)/wndfstest.elf: wndfstest.cpp $(OBJDIR)/log.o $(OBJDIR)/pos.o $(OBJDIR)/keywait.o
	$(COMPILE) $^ $(FUSELIBS) -o $@

# Mouse file tests.
$(TESTDIR)/fsmtest.elf: fsmtest.cpp
	$(COMPILE) $^ -o $@

# Entry tests.
$(TESTDIR)/enttest.elf: enttest.cpp $(OBJDIR)/ent.o $(OBJDIR)/dir.o $(OBJDIR)/file.o $(OBJDIR)/log.o
	$(COMPILE) $^ $(FUSELIBS) -o $@

# Get name tests.
$(TESTDIR)/gntest.elf: gntest.cpp $(OBJDIR)/gn.o
	$(COMPILE) $^ -o $@

# Tests for keyboard.
$(TESTDIR)/kbtest.elf: kbtest.cpp $(OBJDIR)/kb.o $(OBJDIR)/kbc.o $(OBJDIR)/utf8.o
	$(COMPILE) $^ -o $@

# Tests for UTF-8 characters.
$(TESTDIR)/utf8test.elf: utf8test.cpp $(OBJDIR)/utf8.o
	$(COMPILE) $^ -o $@

# Compile display tests.
$(TESTDIR)/dpytests.elf: dpytests.cpp
	$(COMPILE) $< dpy.cpp log.cpp -o $@
