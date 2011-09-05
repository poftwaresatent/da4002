JAVAC= javac

SRCS= $(wildcard *.java)
OBJS= $(SRCS:.java=.class) 

all: $(OBJS)

clean:
	rm -f *.class *~

.SUFFIXES: .java .class

.java.class:
	$(JAVAC) $<
