make pretty: clear all

ugly: all

all: 
	gcc -g -pg -lm cur.c

clear:
	clear

test: pretty
	./a.out test.in
	cat test.out

longtest: pretty
	./a.out test.in > results.out
	cat test.out

clean:
	rm *~

totalclean:
	rm \#*\#
	rm *~