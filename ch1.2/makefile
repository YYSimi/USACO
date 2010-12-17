pretty: clear all

ugly: all

all: 
	gcc -std=c99 -lm -g cur.c

clear:
	clear

test: pretty
	./a.out test.in
	cat test.out

clean:
	rm *~

totalclean:
	rm *~
	rm \#*\#