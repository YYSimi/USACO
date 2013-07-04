make pretty: clear all

ugly: all

all: 
	g++ -g -pg -lm stamps.cpp

clear:
	clear

test: pretty
	./a.out stamps.in
	cat stamps.out

longtest: pretty
	./a.out stamps.in > longtest.out
	cat stamps.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#