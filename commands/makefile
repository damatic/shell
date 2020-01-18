###############################################################################
#
#	File: Makefile
#
#	Description: Makefile for commands
#				 
#	Author: Danijel Matic
#
#
###############################################################################

MKDIR=mkdir
OBJDIR = ../bin
CC=gcc
RM=rm
CFLAGS= -Wall -O3
LDFLAGS=-lm

SOURCES=$(wildcard *.c)

#OBJECTS=$(SOURCES:.c=.o)

#$(info $$OBJECTS is [${OBJECTS}])

EXECS=$(SOURCES:%.c=%)

.PHONY: all clean
all: $(EXECS)

#.c.o:
#	$(CC) $(CFLAGS) $< -o ${OBJDIR}/$@

$(EXECS): %: %.c
	$(MKDIR) -p ../bin
	$(CC) $^ $(LDFLAGS) -o ${OBJDIR}/$@

clean:
#	-@ $(RM) *.o 
	-@ $(RM) ${OBJDIR}/$(EXECS)