CC       = gcc
CFLAGS   = -Wall -O0 -g -pipe
PROGRAMS = $(shell ls *.c | sed 's:\.c$$::')

all:
	for prg in $(PROGRAMS); \
	do \
	  $(MAKE) recurse PRG=$$prg; \
	done

recurse: $(PRG).c Makefile
	$(CC) $(CFLAGS) -o $(PRG) $(PRG).c

clean:
	rm -f *~ *.o $(PROGRAMS)
