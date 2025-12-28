/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef lint
static	char sccsid[] = "@(#)error.c 1.1 94/10/31 SMI"; /* from S5R3.1 1.9 */
#endif

/*
 * UNIX shell
 */

#include	"defs.h"


/* ========	error handling	======== */

scfailed(s)
char	*s;
{
	failed(s, scerrmsg());
}

char *
scerrmsg()
{
	extern int errno;
	return(strerror(errno));
}

void
failed(s1, s2)
	char	*s1, *s2;
{
	prp();
	prs_cntl(s1);
	if (s2)
	{
		prs(colon);
		prs(s2);
	}
	newline();
	exitsh(ERROR);
}

void
error(s)
	char	*s;
{
	failed(s, NIL);
}

void
exitsh(xno)
	int	xno;
{
	/*
	 * Arrive here from `FATAL' errors
	 *  a) exit command,
	 *  b) default trap,
	 *  c) fault with no trap set.
	 *
	 * Action is to return to command level or exit.
	 */
	exitval = xno;
	flags |= eflag;
	if ((flags & (forked | errflg | ttyflg)) != ttyflg)
		done();
	else
	{
		clearup();
		restore(0);
		clear_buff();
		execbrk = breakcnt = funcnt = 0;
		longjmp(errshell, 1);
	}
}

void
done()
{
	register char	*t;

	if (t = trapcom[0])
	{
		trapcom[0] = 0;
		execexp(t, 0);
		sh_free(t);
	}
	else
		chktrap();

	rmtemp(0);
	rmfunctmp();

#ifdef ACCT
	doacct();
#endif
	exit(exitval);
}

void
rmtemp(base)
	void	*base;
{
	while (iotemp > (struct ionod *)base)
	{
		unlink(iotemp->ioname);
		sh_free(iotemp->iolink);
		iotemp = iotemp->iolst;
	}
}

rmfunctmp()
{
	while (fiotemp)
	{
		unlink(fiotemp->ioname);
		fiotemp = fiotemp->iolst;
	}
}

failure(s1, s2)
char	*s1, *s2;
{
	prp();
	prs_cntl(s1);
	if (s2)
	{
		prs(colon);
		prs(s2);
	}
	newline();
	
	if (flags & errflg)
		exitsh(ERROR);

	flags |= eflag;
	exitval = ERROR;
	exitset();
}
