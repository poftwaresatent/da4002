SRCS= $(wildcard *.java)
OBJS= $(SRCS:.java=.class) 

TEX_SRCS= $(wildcard *.tex)
PDFS= $(TEX_SRCS:.tex=.pdf) 

JC= javac
JCFLAGS=

RUBBER= rubber

all: figs $(OBJS) $(PDFS)

figs:
	$(MAKE) -C fig

re: clean
	touch $(SRCS)
	$(MAKE) all

doc: $(SRCS)
	javadoc -d doc $(SRCS)

clean:
	rm -f *.class *~ *.log *.aux *.bbl *.blg $(PDFS)

.SUFFIXES: .java .class .tex .pdf

.java.class:
	$(JC) $(JCFLAGS) $<

.tex.pdf:
	$(RUBBER) -d $<

itads-exam.pdf: $(SRCS)
