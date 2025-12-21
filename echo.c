/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef lint
static	char sccsid[] = "@(#)echo.c 1.1 94/10/31 SMI"; /* from S5R3 1.6 */
#endif

/*
 *	UNIX shell
 */
#include	"defs.h"

#define	exit(a)	flushb();return(a)

extern int exitval;

echo(argc, argv)
char **argv;
{
	register int i, nflg;

	nflg = 0;
	if(argc > 1 && argv[1][0] == '-' && argv[1][1] == 'n') {
		nflg++;
		argc--;
		argv++;
	}
	for(i=1; i<argc; i++) {
		sigchk();
		prs_buff(argv[i]);
		if (i < argc-1)
			prc_buff(' ');
	}
	if(nflg == 0)
		prc_buff('\n');
	exit(0);
}
