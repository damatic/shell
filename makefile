all: main.c builtin.h builtin.c
	gcc -Wall main.c readerParser.h readerParser.c pipe.h pipe.c builtin.h builtin.c -lreadline -o test

clean: test
	rm -r test