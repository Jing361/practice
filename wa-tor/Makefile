CC:=g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c

default:wator

wator:main.o WatorGame.o
	$(CC) main.o WatorGame.o Fish.o Shark.o -o wator

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

Fish.o:Fish.cc Entity.hh Renderable.hh
	$(CC) $(cflags) $(flags) Fish.cc

Shark.o:Shark.cc Entity.hh Renderable.hh
	$(CC) $(cflags) $(flags) Shark.cc

WatorGame.o:Fish.o Shark.o WatorGame.cc
	$(CC) $(cflags) $(flags) WatorGame.cc

clean:
	rm *.o core wator

