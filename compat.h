/* Portability compatibility header for SunOS 4.1.4 sh port */
#ifndef COMPAT_H
#define COMPAT_H

#ifdef __linux__
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#endif

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <fcntl.h>

/* Handle macro redefinitions from system headers */
#undef EOF
#undef BUFSIZ

/* SunOS 4 specific types/macros */
typedef unsigned char unchar;

/* Map renamed internal symbols to system equivalents or provided definitions */
#define sh_sbrk(x) sbrk(x)
#define sh_tmpnam(s) tmpnam(s)

/* Missing signals */
#ifndef SIGEMT
#define SIGEMT 7  /* Traditional BSD value */
#endif

#endif /* COMPAT_H */
