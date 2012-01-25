SRCS= $(wildcard *.java)
OBJS= $(SRCS:.java=.class) 

TEX_SRCS= $(wildcard *.tex)
PDFS= $(TEX_SRCS:.tex=.pdf) 

DOT_SRCS= $(wildcard *.dot)
DOT_PDFS= $(DOT_SRCS:.dot=.pdf)

PDF_SRCS= q4-graph-diagram.pdf

JC= javac
JCFLAGS=

RUBBER= rubber

all: jj $(PDFS)

jj: $(OBJS)

#figs:
#	$(MAKE) -C fig

re: clean
	touch $(SRCS)
	$(MAKE) all

#doc: $(SRCS)
#	javadoc -d doc $(SRCS)

clean:
	rm -f *.class *~ *.log *.aux *.bbl *.blg $(PDFS)

.SUFFIXES: .java .class .tex .pdf .dot

.java.class:
	$(JC) $(JCFLAGS) $<

.tex.pdf: $(DOT_PDFS)
	$(RUBBER) -d $<

.dot.pdf:
	dot -Tpdf -o $@ $<

itads-exam-2012-01-02.pdf: $(TEX_SRCS) $(DOT_PDFS) $(PDF_SRCS) $(wildcard *.txt)
