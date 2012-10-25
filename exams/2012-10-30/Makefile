TEX_SRCS= $(wildcard *.tex)
PDFS= $(TEX_SRCS:.tex=.pdf) 

DOT_SRCS= $(wildcard *.dot)
DOT_PDFS= $(DOT_SRCS:.dot=.pdf)

SVG_SRCS= $(wildcard *.svg)
SVG_PDFS= $(SVG_SRCS:.svg=.pdf)

CC       = gcc
CFLAGS   = -Wall -O0 -g -pipe
PROGRAMS = $(shell ls *.c | sed 's:\.c$$::')

all: programs pdfs

pdfs: $(PDFS)

programs:
	for prg in $(PROGRAMS); \
	do \
	  $(MAKE) recurse PRG=$$prg || exit 42; \
	done

recurse: $(PRG).c Makefile
	$(CC) $(CFLAGS) -o $(PRG) $(PRG).c

re: clean
	touch $(TEX_SRCS)
	$(MAKE) all

clean:
	rm -fr *~ *.o *.dSYM $(PROGRAMS) *.log *.aux *.bbl *.blg $(PDFS)

.SUFFIXES: .tex .pdf .dot

.tex.pdf: $(DOT_PDFS)
	rubber -d $<

.dot.pdf:
	dot -Tpdf -o $@ $<

itads-exam-2012-10-30.pdf: $(TEX_SRCS) $(DOT_PDFS) $(SVG_PDFS) $(wildcard *.txt)
