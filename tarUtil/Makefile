CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++14
dflags:=-ggdb3
cflags:=-c $(dflags)

default:main

main:main.o archive.tar
	$(CC) main.o -o main

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

archive.tar:files/one.txt files/two.txt
	cd files && tar -cf archive.tar one.txt two.txt && mv archive.tar ..

clean:
	rm *.o core main archive.tar one.txt two.txt

