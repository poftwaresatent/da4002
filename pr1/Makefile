CC = gcc
CFLAGS = -Wall

all: insertion-sort-benchmark merge-sort-benchmark check-merge-sort

insertion-sort-benchmark: insertion-sort-benchmark.c Makefile
	$(CC) $(CFLAGS) -o insertion-sort-benchmark insertion-sort-benchmark.c

merge-sort-benchmark: merge-sort-benchmark.c Makefile
	$(CC) $(CFLAGS) -o merge-sort-benchmark merge-sort-benchmark.c

check-merge-sort: check-merge-sort.c test-sorting-algo.o test-sorting-algo.h Makefile
	$(CC) $(CFLAGS) -o check-merge-sort check-merge-sort.c test-sorting-algo.o

test-sorting-algo.o: test-sorting-algo.c test-sorting-algo.h
