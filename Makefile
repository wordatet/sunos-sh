# Portability Makefile for SunOS 4.1.4 shell
CROSS_COMPILE ?= 
CC = $(CROSS_COMPILE)gcc
CFLAGS = -std=gnu89 -O0 -g -DRES -I. -include compat.h \
         -Wno-implicit-int -Wno-implicit-function-declaration -Wno-return-type
OBJS = setbrk.o blok.o stak.o cmd.o fault.o main.o word.o string.o \
       name.o args.o xec.o service.o error.o io.o print.o macro.o expand.o \
       ctype.o msg.o test.o defs.o echo.o hash.o hashserv.o pwd.o func.o

.PHONY: all clean vintage paranoid

all: sh

sh: $(OBJS)
	$(CC) $(CFLAGS) -o sh $(OBJS)

# Vintage Audit: PCC Build (no -include flag, compat.h included via defs.h)
vintage: clean
	$(MAKE) CC=pcc CFLAGS="-g -O0 -DRES -I."

# Stress: Run the Super Paranoid suite
paranoid: clean sh
	./super_paranoid_sunos.sh

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) sh
