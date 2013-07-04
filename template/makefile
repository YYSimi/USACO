make pretty: clear all

ugly: all

all: 
	g++ -g -pg -lm PROGNAME.cpp

clear:
	clear

test: pretty
	./a.out PROGNAME.in
	cat PROGNAME.out

longtest: pretty
	./a.out PROGNAME.in > longtest.out
	cat PROGNAME.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#