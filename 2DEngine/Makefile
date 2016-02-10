CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++14
dflags:=-ggdb3
cflags:=-c

default:main

main:main.o image.o engine.o libMap.so
	$(CC) main.o image.o engine.o -lpthread -ldl -o main

main.o:main.cc buffer.cc physics.cc entity.cc
	$(CC) $(cflags) $(flags) main.cc

image.o:image.cc
	$(CC) $(cflags) $(flags) image.cc

engine.o:engine.cc
	$(CC) $(cflags) $(flags) engine.cc

tarSplit.o:tarSplit.cc
	$(CC) $(cflags) $(flags) tarSplit.cc

libTarSplit.a:tarSplit.o
	ar -cvq libTarSplit.a tarSplit.o

map.tar:data/map.adv data/libMap.so
	cd data && tar -cf map.tar libMap.so map.wld && mv map.tar ..

data/map.o:data/map.cc
	$(CC) $(cflags) $(flags) -fPIC -o data/map.o data/map.cc

libMap.so:data/map.o
	$(CC) -shared -o libMap.so data/map.o

clean:
	rm *.o core main

