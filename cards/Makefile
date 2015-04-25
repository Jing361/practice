CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)

name:=main

default:main

main:main.o geneticAlgorithm.o
	$(CC) geneticAlgorithm.o main.o -o $(name)

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

geneticAlgorithm.o:geneticAlgorithm.cc
	$(CC) $(cflags) $(flags) geneticAlgorithm.cc

clean:
	rm *.o core $(name)

