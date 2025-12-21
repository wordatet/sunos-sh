# Makefile for SunOS 4.1.4 shell port
CROSS_COMPILE ?= 
CC = $(CROSS_COMPILE)gcc
CFLAGS = -std=gnu89 -O0 -g -DRES -I. -include compat.h \
         -Wno-implicit-int -Wno-implicit-function-declaration -Wno-return-type \
         -Wno-int-conversion -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast

OBJS = setbrk.o blok.o stak.o cmd.o fault.o main.o word.o string.o \
       name.o args.o xec.o service.o error.o io.o print.o macro.o expand.o \
       ctype.o msg.o test.o defs.o echo.o hash.o hashserv.o pwd.o func.o

sh: $(OBJS)
	$(CC) $(CFLAGS) -o sh $(OBJS)

clean:
	rm -f $(OBJS) sh
