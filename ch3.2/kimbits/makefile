make pretty: clear all

ugly: all

all: 
	g++ -g -pg -lm kimbits.cpp

clear:
	clear

test: pretty
	./a.out kimbits.in
	cat kimbits.out

longtest: pretty
	./a.out kimbits.in > longtest.out
	cat kimbits.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#