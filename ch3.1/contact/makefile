make pretty: clear all

ugly: all

all: 
	g++ -g -pg -lm contact.cpp

clear:
	clear

test: pretty
	./a.out contact.in
	cat contact.out

longtest: pretty
	./a.out contact.in > longtest.out
	cat contact.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#