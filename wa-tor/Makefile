CC:=g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c

default:wator

wator:main.o
	$(CC) main.o -o wator

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

clean:
	rm *.o core main

