CC       = gcc
CFLAGS   = -Wall -O0 -g -pipe
HEADERS  = $(shell ls *.h)
OBJECTS  = $(shell ls *.c | grep -v -e '^main-' -e '^test-' | sed 's:\.c$$:.o:')
PROGRAMS = $(shell ls main-*.c test-*.c | sed 's:\.c$$::')

all:
	for prg in $(PROGRAMS); \
	do \
	  $(MAKE) recurse PRG=$$prg || exit 42; \
	done

recurse: $(PRG).c Makefile $(HEADERS) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PRG) $(PRG).c $(OBJECTS)

clean:
	rm -fr *~ *.o *.dSYM $(PROGRAMS)
