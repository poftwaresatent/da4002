CXX= g++
CPPFLAGS= -Wall -I/opt/local/include
CXXFLAGS= $(CPPFLAGS) -pipe -O0 -g -arch i386
LDFLAGS= -L/opt/local/lib -lpng -lm -arch i386

all: png2txt

png2txt: png2txt.o
	$(CXX) -o png2txt png2txt.o $(OBJS) $(LDFLAGS)

clean:
	rm -f *~ *.o png2txt
