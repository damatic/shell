OBJDIR = $(HOME)/shell/obj_output

all: copy list mkd move cat chmod wc rm ps kill head mkf
	-mkdir -p $(OBJDIR)
	
copy: copy.c
	gcc -Wall copy.c -o $(OBJDIR)/copy

list: list.c
	gcc -Wall list.c -o $(OBJDIR)/list

mkd: mkd.c
	gcc -Wall mkd.c -o $(OBJDIR)/mkd

move: move.c
	gcc -Wall move.c -o $(OBJDIR)/move
	
cat: cat.c
	gcc -Wall cat.c -o $(OBJDIR)/cat

chmod: chmod.c
	gcc -Wall chmod.c -o $(OBJDIR)/chmod

wc: wc.c
	gcc -Wall wc.c -o $(OBJDIR)/wc
	
rm: rm.c
	gcc -Wall rm.c -o $(OBJDIR)/rm

ps: printproc.c
	gcc -Wall printproc.c -o $(OBJDIR)/ps

kill: kill.c
	gcc -Wall kill.c -o $(OBJDIR)/kill
	
head: headproc.c
	gcc -Wall headproc.c -o $(OBJDIR)/head

mkf: mkf.c
	gcc -Wall mkf.c -o $(OBJDIR)/mkf

clean:
	rm -r $(OBJDIR)/*
