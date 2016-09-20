CC=g++
CFLAGS=-Wall --std=c++14

all: bin/salesman

bin/salesman: bin/generator.o bin/solver.o
	$(CC) $(CFLAGS) bin/generator.o bin/solver.o -o bin/salesman

bin/generator.o:
	$(CC) $(CFLAGS) -c generator.cpp -o bin/generator.o

bin/solver.o:
	$(CC) $(CFLAGS) -c solver.cpp -o bin/solver.o


clean:
	rm bin/*

.PHONY: clean

$(shell mkdir -p bin)
