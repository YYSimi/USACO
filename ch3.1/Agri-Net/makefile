make pretty: clear all

ugly: all

all: 
	g++ -g -pg -lm cur.cpp

clear:
	clear

test: pretty
	./a.out test.in
	cat agrinet.out

longtest: pretty
	./a.out test.in > longtest.out
	cat agrinet.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#