CC=g++
LFLAGS=-lSDL2 -lSDL2_ttf
CFLAGS=-c -g -pedantic -std=c++17

main: main.o
	${CC} main.o -o main ${LFLAGS}

main.o: main.cpp map.hpp
	${CC} ${CFLAGS} main.cpp

.PHONY: clean
clean:
	rm -rf *.o main

.PHONY: run
run:
	./main
