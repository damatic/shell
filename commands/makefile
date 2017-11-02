all: copy list mkd move cat chmod wc rm

copy: copy.c
	gcc -Wall copy.c -o copy

list: list.c
	gcc -Wall list.c -o list

mkd: mkd.c
	gcc -Wall mkd.c -o mkd

move: move.c
	gcc -Wall move.c -o move
	
cat: cat.c
	gcc -Wall cat.c -o cat

chmod: chmod.c
	gcc -Wall chmod.c -o chmod

wc: wc.c
	gcc -Wall wc.c -o wc
	
rm: rm.c
	gcc -Wall rm.c -o rm

clean: copy list mkd move cat chmod wc rm
	rm -r copy list mkd move cat chmod wc rm