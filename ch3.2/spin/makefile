make pretty: clear all

ugly: all

all: 
	g++ -g -pg -lm spin.cpp

clear:
	clear

test: pretty
	./a.out spin.in
	cat spin.out

longtest: pretty
	./a.out spin.in > longtest.out
	cat spin.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#