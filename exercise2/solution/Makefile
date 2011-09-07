SRCS= $(wildcard *.java)
OBJS= $(SRCS:.java=.class) 

JC= javac
JCFLAGS= -classpath ../..

all: $(OBJS)

doc: $(SRCS)
	javadoc -d doc $(SRCS)

clean:
	rm -f *.class *~

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JCFLAGS) $<
