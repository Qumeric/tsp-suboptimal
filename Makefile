CC=g++
CFLAGS=-Wall --std=c++14

all: bin/salesman

bin/salesman: bin/generator.o bin/solver.o bin/bruteforce.o bin/closestN.o bin/ant.o bin/annealing.o
	$(CC) $(CFLAGS) bin/generator.o bin/solver.o bin/bruteforce.o bin/closestN.o bin/ant.o bin/annealing.o -o bin/salesman

bin/generator.o:
	$(CC) $(CFLAGS) -c generator.cpp -o bin/generator.o

bin/solver.o:
	$(CC) $(CFLAGS) -c solver.cpp -o bin/solver.o

bin/bruteforce.o:
	$(CC) $(CFLAGS) -c bruteforce.cpp -o bin/bruteforce.o

bin/closestN.o:
	$(CC) $(CFLAGS) -c closestN.cpp -o bin/closestN.o

bin/ant.o:
	$(CC) $(CFLAGS) -c ant.cpp -o bin/ant.o

bin/annealing.o:
	$(CC) $(CFLAGS) -c annealing.cpp -o bin/annealing.o

clean:
	rm bin/*

.PHONY: clean

$(shell mkdir -p bin)
