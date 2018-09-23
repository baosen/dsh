###########
# OBJECTS #
###########

all: \
	$(OBJDIR)/log.o \
	$(OBJDIR)/fb.o \
	$(OBJDIR)/pix.o \
	$(OBJDIR)/scr.o \
	$(OBJDIR)/fs.o \
	$(OBJDIR)/ent.o \
	$(OBJDIR)/file.o \
	$(OBJDIR)/dir.o \
	$(OBJDIR)/kbf.o \
	$(OBJDIR)/m.o \
	$(OBJDIR)/mf.o \
	$(OBJDIR)/wndd.o \
	$(OBJDIR)/wndx.o \
	$(OBJDIR)/wndy.o \
	$(OBJDIR)/wndxc.o \
	$(OBJDIR)/wndyc.o \
	$(OBJDIR)/wndctl.o

# Log module.
$(OBJDIR)/log.o: log.cpp $(INCDIR)/log.hpp
	$(COMPILE) -c $< -o $@

# Framebuffer module.
$(OBJDIR)/fb.o: fb.cpp scr.o log.o
	$(COMPILE) -c $< -o $@

# Screen module.
$(OBJDIR)/scr.o: scr.cpp
	$(COMPILE) -c $< -o $@

# File system.
$(OBJDIR)/fs.o: fs.cpp $(INCDIR)/fs.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# File system entries.
$(OBJDIR)/ent.o: ent.cpp $(INCDIR)/ent.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# File entries.
$(OBJDIR)/file.o: file.cpp $(INCDIR)/file.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Directory entries.
$(OBJDIR)/dir.o: dir.cpp $(INCDIR)/dir.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Keyboard file.
$(OBJDIR)/kbf.o: kbf.cpp $(INCDIR)/kbf.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Mouse file.
$(OBJDIR)/mf.o: mf.cpp $(INCDIR)/mf.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window directory.
$(OBJDIR)/wndd.o: wndd.cpp $(INCDIR)/wndd.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window x coordinate file.
$(OBJDIR)/wndx.o: wndx.cpp $(INCDIR)/wndy.hpp gn.o
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window y coordinate file.
$(OBJDIR)/wndy.o: wndy.cpp $(INCDIR)/wndy.hpp gn.o
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window x ASCII coordinate file.
$(OBJDIR)/wndxc.o: wndxc.cpp $(INCDIR)/wndxc.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window y ASCII coordinate file.
$(OBJDIR)/wndyc.o: wndyc.cpp $(INCDIR)/wndyc.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

# Window ctl.
$(OBJDIR)/wndctl.o: wndctl.cpp $(INCDIR)/wndctl.hpp
	$(COMPILE) -c $< $(FUSELIBS) -o $@

$(OBJDIR)/%.o: %.cpp
	$(COMPILE) -c $< -o $@
