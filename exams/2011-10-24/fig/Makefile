DOT_SRCS= $(wildcard *.dot)
PDFS= $(DOT_SRCS:.dot=.pdf) 

all: $(PDFS)

.SUFFIXES: .dot .pdf

.dot.pdf:
	dot -Tpdf -o $@ $<

clean:
	rm -f *~ $(PDFS)
