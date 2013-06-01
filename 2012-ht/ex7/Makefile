#
# Semi-generic Makefile for C projects that are split across several
# source files. If you adhere to the following filename conventions,
# you will probably not need to adjust anything in this file:
#
# - filenames that match `test*.c' or `main*.c' are assumed to be
#   sources for executables (i.e. they must contain a main function)
#
# - all other .c files are assumed to be implementations of
#   functionality required by the executables (or other .c files), in
#   other words they must not contain a main function.
#
# The dependency rules here are a little simplistic, if you get weird
# build errors maybe a `make clean' before another `make' can help.
#

CC       = gcc
CFLAGS   = -Wall -O0 -g -pipe
HEADERS  = $(shell ls *.h)
OBJECTS  = $(shell ls *.c | grep -v -e '^main' -e '^test' | sed 's:\.c$$:.o:')
PROGRAMS = $(shell ls main*.c test*.c | sed 's:\.c$$::')

all:
	for prg in $(PROGRAMS); \
	do \
	  $(MAKE) recurse PRG=$$prg || exit 42; \
	done

recurse: $(PRG).c Makefile $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PRG) $(PRG).c $(OBJECTS)

clean:
	rm -fr *~ *.o *.dSYM $(PROGRAMS) *.dot
