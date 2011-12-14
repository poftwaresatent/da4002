SRCS= $(wildcard *.java)
OBJS= $(SRCS:.java=.class) 

TEX_SRCS= $(wildcard *.tex)
PDFS= $(TEX_SRCS:.tex=.pdf) 

DOT_SRCS= $(wildcard *.dot)
DOT_PDFS= $(DOT_SRCS:.dot=.pdf)

JC= javac
JCFLAGS=

RUBBER= rubber

all: $(OBJS) $(PDFS)

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

itads-exam-2012-01-02.pdf: $(SRCS) $(TEX_SRCS) $(DOT_SRCS)
