CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++14
dflags:=-ggdb3
cflags:=-c $(dflags)

default:main

main:main.o
	$(CC) main.o -o main
	tar -cf archive.tar files/one.txt files/two.txt

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

clean:
	rm *.o core main

