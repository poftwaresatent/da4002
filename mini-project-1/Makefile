SRCS= $(wildcard *.java)
OBJS= $(SRCS:.java=.class) 

all: $(OBJS)

doc:
	javadoc -d doc $(SRCS)

clean:
	rm -f *.class *~

.SUFFIXES: .java .class

.java.class:
	$(javac) $<
