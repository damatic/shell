#Make that compiles and creates commands

OBJDIR = ../obj_output
CC=gcc
RM=rm
CFLAGS= -Wall -O3
LDFLAGS=-lm

SOURCES=$(wildcard *.c)

#OBJECTS=$(SOURCES:.c=.o)

#$(info $$OBJECTS is [${OBJECTS}])

EXECS=$(SOURCES:%.c=%)

.PHONY: all
all: $(EXECS)

#.c.o:
#	$(CC) $(CFLAGS) $< -o ${OBJDIR}/$@

$(EXECS): %: %.c
	$(CC) $^ $(LDFLAGS) -o ${OBJDIR}/$@

.PHONY: clean
clean:
#	-@ $(RM) *.o 
	-@ $(RM) ${OBJDIR}/$(EXECS)