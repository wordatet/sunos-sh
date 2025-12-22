# Portability Makefile for SunOS 4.1.4 shell
CROSS_COMPILE ?= 
CC = $(CROSS_COMPILE)gcc
CFLAGS = -std=gnu89 -O0 -g -DRES -I. -include compat.h \
         -Wno-implicit-int -Wno-implicit-function-declaration -Wno-return-type \
         -Wno-incompatible-pointer-types -Wno-int-conversion \
         -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast
OBJS = setbrk.o blok.o stak.o cmd.o fault.o main.o word.o string.o \
       name.o args.o xec.o service.o error.o io.o print.o macro.o expand.o \
       ctype.o msg.o test.o defs.o echo.o hash.o hashserv.o pwd.o func.o

.PHONY: all clean

all: sh

sh: $(OBJS)
	$(CC) $(CFLAGS) -o sh $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) sh
