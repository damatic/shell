all: main.c builtin.h builtin.c
	gcc -Wall main.c builtin.h builtin.c -o test

clean: test
	rm -r test