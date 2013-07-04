make pretty: clear all

ugly: all

all: 
	gcc -g -pg -lm inflate.cpp

clear:
	clear

test: pretty
	./a.out inflate.in
	cat inflate.out

longtest: pretty
	./a.out inflate.in > longtest.out
	cat inflate.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#