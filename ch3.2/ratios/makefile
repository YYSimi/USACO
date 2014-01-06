make pretty: clear all

ugly: all

all: 
	g++ -g -pg -lm ratios.cpp

clear:
	clear

test: pretty
	./a.out ratios.in
	cat ratios.out

longtest: pretty
	./a.out ratios.in > longtest.out
	cat ratios.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#