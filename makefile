# TODO: Set the number of parallell jobs to be run to be equal to the number of CPU cores.
#CPUS      ?= $(shell sysctl -n hw.ncpu || echo 1)
#MAKEFLAGS += --jobs=$(CPUS)

export ARCH = x86_64

# Set the directory where the built artifacts would be built into.
BUILDDIR = $(PWD)/build

# Set the directory where the executables would be built into.
export BINDIR = $(BUILDDIR)/$(ARCH)/bin

# Set the directory where the tests would be built into.
export TESTDIR = $(BUILDDIR)/$(ARCH)/tests

# Set the directory where the object files would be built into.
export OBJDIR = $(BUILDDIR)/$(ARCH)/obj

# Set the directory containing the header files to include.
export INCDIR = $(PWD)/include

# Set the directory containing the source code of the libraries.
#LIBDIR   = lib/

# Set the directory containing the source code for fuse main.
#SRCDIR   = src/


# Set C++ compiler.
export CXX = g++
# Set C++ compiler flags.
export CXXFLAGS = -I$(INCDIR) -std=c++17 -O3 -Wall -Wextra

# Compile command.
export COMPILE = @$(CXX) $(CXXFLAGS)

# FUSE libraries.
export FUSELIBS = `pkg-config fuse --cflags --libs`


.PHONY: all lib tests bin clean

# Build everything.
all: lib tests bin

lib:
	$(MAKE) -C lib

tests: lib
	$(MAKE) -C tests

bin: lib
	$(MAKE) -C bin

# Remove built files.
#clean:
#	@rm -rf *.o $(BINS) $(OBJDIR)
