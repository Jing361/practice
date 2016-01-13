CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++14
dflags:=-ggdb3
cflags:=-c

default:main

main:main.o image.o engine.o
	$(CC) main.o image.o engine.o -lpthread -o main

main.o:main.cc buffer.cc physics.cc entity.cc
	$(CC) $(cflags) $(flags) main.cc

image.o:image.cc
	$(CC) $(cflags) $(flags) image.cc

engine.o:engine.cc
	$(CC) $(cflags) $(flags) engine.cc

clean:
	rm *.o core main

