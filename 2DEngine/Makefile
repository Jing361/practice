CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++14
dflags:=-ggdb3
cflags:=-c

default:main

main:main.o image.o
	$(CC) main.o image.o -o main

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

image.o:image.cc
	$(CC) $(cflags) $(flags) image.cc

clean:
	rm *.o core main

