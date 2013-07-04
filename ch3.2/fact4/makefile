make pretty: clear all

ugly: all

all: 
	g++ -g -pg -lm fact4.cpp

clear:
	clear

test: pretty
	./a.out fact4.in
	cat fact4.out

longtest: pretty
	./a.out fact4.in > longtest.out
	cat fact4.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#