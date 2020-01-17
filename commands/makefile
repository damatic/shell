#Make that compiles and creates commands

OBJDIR = ../obj_output

CC=gcc

RM=rm

CFLAGS= -Wall -O3

LDFLAGS=-lm

SOURCES=$(wildcard *.c)

$(info $$SOURCES is [${SOURCES}])

#OBJECTS=$(SOURCES:.c=.o)

#$(info $$OBJECTS is [${OBJECTS}])

EXECS=$(SOURCES:%.c=%)

$(info $$EXECS is [${EXECS}])

.PHONY: all
all: $(EXECS)

#.c.o:
#	$(CC) $(CFLAGS) $< -o ${OBJDIR}/$@

$(EXECS): %: %.c
	$(CC) $^ $(LDFLAGS) -o ${OBJDIR}/$@

.PHONY: clean
clean:
	-@ $(RM) *.o 
	-@ $(RM) $(EXECS)