CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++14
#debug flags
dflags:=-ggdb3
#valgrind flags
gflags:=-O0 $(dflags)
cflags:=-c $(dflags)
files:=main Fish Shark WatorGame WatorWorld
objects:=$(files:=.o)
source:=$(files:=.cc)

default:wator

wator:main.o WatorGame.o WatorWorld.o Fish.o Shark.o
	$(CC) main.o WatorWorld.o WatorGame.o Fish.o Shark.o -o wator

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

Fish.o:Fish.cc Entity.hh Renderable.hh
	$(CC) $(cflags) $(flags) Fish.cc

Shark.o:Shark.cc Entity.hh Renderable.hh
	$(CC) $(cflags) $(flags) Shark.cc

WatorGame.o:WatorGame.cc
	$(CC) $(cflags) $(flags) WatorGame.cc

WatorWorld.o:WatorWorld.cc World.hh
	$(CC) $(cflags) $(flags) WatorWorld.cc

clean:
	rm *.o core wator

