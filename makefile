all: main.c builtin.h builtin.c
	gcc -Wall main.c pipe.h pipe.c builtin.h builtin.c -o test

clean: test
	rm -r test