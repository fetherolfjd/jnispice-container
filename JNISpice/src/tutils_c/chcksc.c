/* chcksc.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure      CHCKSC ( Check scalar character string ) */

/* Subroutine */ int chcksc_(char *name__, char *val, char *comp, char *exp__,
	 logical *ok, ftnlen name_len, ftnlen val_len, ftnlen comp_len, 
	ftnlen exp_len)
{
    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer i_len(char *, ftnlen), s_cmp(char *, char *, ftnlen, ftnlen);
    logical l_ge(char *, char *, ftnlen, ftnlen), l_le(char *, char *, ftnlen,
	     ftnlen), l_lt(char *, char *, ftnlen, ftnlen), l_gt(char *, char 
	    *, ftnlen, ftnlen);

    /* Local variables */
    logical fail;
    char good[120];
    integer lval, lexp;
    extern /* Subroutine */ int ucase_(char *, char *, ftnlen, ftnlen), 
	    repmc_(char *, char *, char *, char *, ftnlen, ftnlen, ftnlen, 
	    ftnlen);
    char myval[4000];
    extern integer rtrim_(char *, ftnlen);
    char myexp[4000], messge[320];
    extern logical verbos_(void);
    char mycomp[4];
    extern /* Subroutine */ int tstlog_(char *, logical *, ftnlen), tstlgs_(
	    char *, char *, ftnlen, ftnlen);
    char bad[120];
    extern /* Subroutine */ int tststy_(char *, char *, ftnlen, ftnlen);


/* $ Abstract */

/*     Check an string scalar value against some expected value. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*      None. */

/* $ Keywords */

/*       TESTING */

/* $ Declarations */


/* $ Brief_I/O */

/*      VARIABLE  I/O  DESCRIPTION */
/*      --------  ---  -------------------------------------------------- */
/*      NAME       I   the name of the variable to be examined. */
/*      VAL        I   the actual variable */
/*      EXP        I   the comparison value for the variable */
/*      COMP       I   the kind of comparison to perform. */
/*      OK         O   TRUE if the test passes, FALSE otherwise.. */

/* $ Detailed_Input */

/*     NAME        is the string used to give the name of a variable */

/*     VAL         is the actual character variable to be examined */

/*     EXP         an expected value or bound on the value VAL. */

/*                    =    ---   check for strict equality */
/*                    >    ---   check for VAL >  EXP */
/*                    <    ---   check for VAL <  EXP */
/*                    >=   ---   check for VAL >= EXP ( LGE (VAL, EXP) ) */
/*                    <=   ---   check for VAL <= EXP ( LLE (VAL, EXP) ) */
/*                    !=   ---   check for VAL != EXP ( VAL .NE. EXP   ) */

/*                    The following are the case insensitive versions */
/*                    of the previous checks. */

/*                    ~=    ---   check for strict equality */
/*                    ~>    ---   check for VAL >  EXP */
/*                    ~<    ---   check for VAL <  EXP */
/*                    ~>=   ---   check for VAL >= EXP */
/*                    ~<=   ---   check for VAL <= EXP */
/*                    ~!=   ---   check for VAL != EXP */

/* $ Detailed_Output */

/*     OK         if the check of the input variable is successful then */
/*                OK is given the value TRUE.  Otherwise OK is given the */
/*                value FALSE and a diagnostic message is sent to the */
/*                test logger. */

/* $ Parameters */

/*      None. */

/* $ Exceptions */

/*     Error free. */

/* $ Files */

/*      The result of a failure is automatically logged in the testing */
/*      log file and failure file.  Success is logged only if verbose */
/*      testing has been enabled. */


/* $ Particulars */

/*     This routine handles a wide variety of comparisons between */
/*     scalar string values. */

/* $ Examples */

/*     Suppose that you have just made a call to a subroutine that */
/*     you wish to test (call the routine SPUD) and you would like */
/*     to test an output string against an expected value.  Using */
/*     this routine you can automatically have the test result logged */
/*     in via the testing utilities. */

/*        CALL SPUD   (  INPUT,   OUTPUT ) */
/*        CALL CHCKSC ( 'OUTPUT', OUTPUT, '=', EXPECT, OK ) */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     W.L. Taber      (JPL) */
/*     B.V. Semenov    (JPL) */

/* $ Version */

/* -    Testing Utility Version 1.1.0, 05-AUG-2013 (BVS) */

/*        Tweaked logic to do only necessary output message construction */
/*        operations to speed-up execution. */

/* -    Testing Utilities Version 1.0.1, 10-JAN-2006 (BVS) */

/*        Removed erroneous cut-n-paste lines from Brief_I/O section of */
/*        the header. */

/* -    Testing Utilities Version 1.0.0, 8-Nov-1994 (WLT) */


/* -& */

/*     Test Utility functions */


/*     SPICELIB functions */


/*     Local Variables */

    tststy_(good, bad, (ftnlen)120, (ftnlen)120);
    tstlgs_("LEFT 3 RIGHT 75 NEWLINE /cr ", "LEFT 3 RIGHT 75 NEWLINE /cr FLA"
	    "G --- LEADER ---", (ftnlen)28, (ftnlen)47);

/*     Set placeholder message. */

    s_copy(messge, "This is a placeholder message that should have never bee"
	    "n displayed. It indicates a CHCKSC bug.", (ftnlen)320, (ftnlen)95)
	    ;
    lval = i_len(val, val_len);
    lexp = i_len(exp__, exp_len);
    s_copy(myval, val, (ftnlen)4000, val_len);
    s_copy(myexp, exp__, (ftnlen)4000, exp_len);
    if (*(unsigned char *)comp == '~') {
	s_copy(mycomp, comp + 1, (ftnlen)4, comp_len - 1);
	ucase_(myval, myval, (ftnlen)4000, (ftnlen)4000);
	ucase_(myexp, myexp, (ftnlen)4000, (ftnlen)4000);
    } else {
	s_copy(mycomp, comp, (ftnlen)4, comp_len);
    }
    fail = FALSE_;
    if (s_cmp(mycomp, "=", (ftnlen)4, (ftnlen)1) == 0) {
	fail = s_cmp(myval, myexp, lval, lexp) != 0;
	if (fail) {
	    s_copy(messge, "The value of # was not the value expected./crThe"
		    " value was:/cr(3:) '#' /cr(-3:) the expected value was:/"
		    "cr(3:) '#'. ", (ftnlen)320, (ftnlen)116);
	    repmc_(messge, "#", name__, messge, (ftnlen)320, (ftnlen)1, 
		    rtrim_(name__, name_len), (ftnlen)320);
	    repmc_(messge, "#", myval, messge, (ftnlen)320, (ftnlen)1, lval, (
		    ftnlen)320);
	    repmc_(messge, "#", myexp, messge, (ftnlen)320, (ftnlen)1, lexp, (
		    ftnlen)320);
	}
    } else if (s_cmp(mycomp, "<", (ftnlen)4, (ftnlen)1) == 0) {
	fail = l_ge(myval, myexp, lval, lexp);
	if (fail) {
	    s_copy(messge, "The value of # was not less than '#' as was expe"
		    "cted. /cr The value was: '#'. ", (ftnlen)320, (ftnlen)78);
	    repmc_(messge, "#", name__, messge, (ftnlen)320, (ftnlen)1, 
		    rtrim_(name__, name_len), (ftnlen)320);
	    repmc_(messge, "#", myexp, messge, (ftnlen)320, (ftnlen)1, lexp, (
		    ftnlen)320);
	    repmc_(messge, "#", myval, messge, (ftnlen)320, (ftnlen)1, lval, (
		    ftnlen)320);
	}
    } else if (s_cmp(mycomp, ">", (ftnlen)4, (ftnlen)1) == 0) {
	fail = l_le(myval, myexp, lval, lexp);
	if (fail) {
	    s_copy(messge, "The value of # was not greater than '#' as was e"
		    "xpected. /cr The value was: '#'. ", (ftnlen)320, (ftnlen)
		    81);
	    repmc_(messge, "#", name__, messge, (ftnlen)320, (ftnlen)1, 
		    rtrim_(name__, name_len), (ftnlen)320);
	    repmc_(messge, "#", myexp, messge, (ftnlen)320, (ftnlen)1, lexp, (
		    ftnlen)320);
	    repmc_(messge, "#", myval, messge, (ftnlen)320, (ftnlen)1, lval, (
		    ftnlen)320);
	}
    } else if (s_cmp(mycomp, ">=", (ftnlen)4, (ftnlen)2) == 0) {
	fail = l_lt(myval, myexp, lval, lexp);
	if (fail) {
	    s_copy(messge, "The value of # was not greater than '#' as was e"
		    "xpected. /cr The value was: '#'. ", (ftnlen)320, (ftnlen)
		    81);
	    repmc_(messge, "#", name__, messge, (ftnlen)320, (ftnlen)1, 
		    rtrim_(name__, name_len), (ftnlen)320);
	    repmc_(messge, "#", myexp, messge, (ftnlen)320, (ftnlen)1, lexp, (
		    ftnlen)320);
	    repmc_(messge, "#", myval, messge, (ftnlen)320, (ftnlen)1, lval, (
		    ftnlen)320);
	}
    } else if (s_cmp(mycomp, "<=", (ftnlen)4, (ftnlen)2) == 0) {
	fail = l_gt(myval, myexp, lval, lexp);
	if (fail) {
	    s_copy(messge, "The value of # was not less than '#' as was expe"
		    "cted. /cr The value was: '#'. ", (ftnlen)320, (ftnlen)78);
	    repmc_(messge, "#", name__, messge, (ftnlen)320, (ftnlen)1, 
		    rtrim_(name__, name_len), (ftnlen)320);
	    repmc_(messge, "#", myexp, messge, (ftnlen)320, (ftnlen)1, lexp, (
		    ftnlen)320);
	    repmc_(messge, "#", myval, messge, (ftnlen)320, (ftnlen)1, lval, (
		    ftnlen)320);
	}
    } else if (s_cmp(mycomp, "!=", (ftnlen)4, (ftnlen)2) == 0) {
	fail = s_cmp(myval, myexp, lval, lexp) == 0;
	if (fail) {
	    s_copy(messge, "The value of # should have been different from '"
		    "#'./cr It wasn't. ", (ftnlen)320, (ftnlen)66);
	    repmc_(messge, "#", name__, messge, (ftnlen)320, (ftnlen)1, 
		    rtrim_(name__, name_len), (ftnlen)320);
	    repmc_(messge, "#", myexp, messge, (ftnlen)320, (ftnlen)1, lexp, (
		    ftnlen)320);
	}
    } else {
	fail = TRUE_;
	s_copy(messge, "The comparison # is not recognized. ", (ftnlen)320, (
		ftnlen)36);
	repmc_(messge, "#", comp, messge, (ftnlen)320, (ftnlen)1, rtrim_(comp,
		 comp_len), (ftnlen)320);
    }
    if (! fail) {
	if (verbos_()) {
	    s_copy(messge, "The comparison/cr/cr(3:) # # '#' /cr/cr(-3:)was "
		    "satisfied./crThe value of # was '#'. ", (ftnlen)320, (
		    ftnlen)85);
	    repmc_(messge, "#", name__, messge, (ftnlen)320, (ftnlen)1, 
		    rtrim_(name__, name_len), (ftnlen)320);
	    repmc_(messge, "#", comp, messge, (ftnlen)320, (ftnlen)1, rtrim_(
		    comp, comp_len), (ftnlen)320);
	    repmc_(messge, "#", myexp, messge, (ftnlen)320, (ftnlen)1, lexp, (
		    ftnlen)320);
	    repmc_(messge, "#", name__, messge, (ftnlen)320, (ftnlen)1, 
		    rtrim_(name__, name_len), (ftnlen)320);
	    repmc_(messge, "#", myval, messge, (ftnlen)320, (ftnlen)1, lval, (
		    ftnlen)320);
	    tstlog_(" ", &fail, (ftnlen)1);
	    tstlog_(messge, &fail, (ftnlen)320);
	}
    } else {
	tstlog_(" ", &fail, (ftnlen)1);
	tstlog_(messge, &fail, (ftnlen)320);
    }
    tstlgs_(good, bad, (ftnlen)120, (ftnlen)120);
    *ok = ! fail;
    return 0;
} /* chcksc_ */

