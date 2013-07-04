make pretty: clear all

ugly: all

all: 
	gcc -g -pg -lm humble.cpp

clear:
	clear

test: pretty
	./a.out humble.in
	cat humble.out

longtest: pretty
	./a.out humble.in > longtest.out
	cat humble.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#