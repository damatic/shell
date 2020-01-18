


all: main.c builtin.h builtin.c
	gcc -Wall main.c readerParser.h readerParser.c pipe.h pipe.c builtin.h builtin.c -lreadline -o shell_start

clean: shell_start
	rm -r shell_start
