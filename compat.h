/* Portability compatibility header for SunOS 4.1.4 sh port */
#ifndef COMPAT_H
#define COMPAT_H

/* PCC compatibility shims - must come BEFORE system headers */
#ifdef __PCC__
#ifndef __attribute__
#define __attribute__(x)
#endif
#ifndef __cold__
#define __cold__
#endif
#ifndef __leaf__
#define __leaf__
#endif
#ifndef __throw
#define __throw
#endif
#ifndef __THROW
#define __THROW
#endif
#ifndef __nonnull
#define __nonnull(x)
#endif
#ifndef __wur
#define __wur
#endif
#ifndef __warn_unused_result__
#define __warn_unused_result__
#endif
#ifndef MB_LEN_MAX
#define MB_LEN_MAX 16
#endif
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif
#endif /* __PCC__ */

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
