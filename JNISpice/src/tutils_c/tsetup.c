/* tsetup.f -- translated by f2c (version 19980913).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* $Procedure TSETUP ( Test utility setup ) */
/* Subroutine */ int tsetup_(char *cmline, char *lognam, char *versn, ftnlen 
	cmline_len, ftnlen lognam_len, ftnlen versn_len)
{
    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_cmp(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    static char word[32];
    extern /* Subroutine */ int ucase_(char *, char *, ftnlen, ftnlen);
    extern logical seton_(char *, ftnlen);
    static logical dummy, on;
    extern /* Subroutine */ int erract_(char *, char *, ftnlen, ftnlen);
    extern logical setoff_(char *, ftnlen);
    extern /* Subroutine */ int errdev_(char *, char *, ftnlen, ftnlen);
    extern logical verbon_(void);
    extern /* Subroutine */ int lckout_(char *, ftnlen);
    static char hstyle[128];
    extern /* Subroutine */ int nextwd_(char *, char *, char *, ftnlen, 
	    ftnlen, ftnlen);
    static char lstyle[128];
    extern /* Subroutine */ int tstlgs_(char *, char *, ftnlen, ftnlen), 
	    tstlcy_(void);
    static char sstyle[128];
    extern /* Subroutine */ int tstopl_(char *, char *, ftnlen, ftnlen);
    static char vstyle[128];

/* $ Abstract */

/*     This routine handles the initializations needed for making use */
/*     of the SPICE testing utilities. */

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

/*     None. */

/* $ Keywords */

/*     TESTING */
/*     INTERFACE */

/* $ Declarations */
/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     CMLINE     I   The command line string. */
/*     LOGNAM     I   Name pattern of file where commands will be logged. */
/*     VERSN      I   Program name and version. */

/* $ Detailed_Input */

/*     CMLINE    the command line line string containing any options */
/*               to modify the test run behavior. */

/*               Accepted option flags: */

/*                  -V   activate verbose logging. This logs every test */
/*                       comparison performed.  You should probably never */
/*                       use this option. */

/*                  -C   activate the logging of individual test cases. */

/*                  -D   activate debugging mode, files are not */
/*                       automatically deleted when a new test family is */
/*                       initiated. */

/*                  -Q   suppress output to standard out. */

/*                  CMLINE is case insensitive. */

/*     LOGNAM    is a pattern to use when creating the name of */
/*               a file to which all commands will be written. */
/*               This can be hard coded in the calling */
/*               program, or may be determined by a file naming */
/*               convention such as is provided by Christen */
/*               and NOMEN. */

/*     VERSN     is a string that may contain anything you would */
/*               like to appear as descriptive text in the first */
/*               line of the log file (and possibly in the greeting */
/*               presented by the program)  Something like */
/*               '<program name> --- Version X.Y' would be appropriate. */
/*               For example if your programs name is KINDLE and you */
/*               are at version 4.2.3 of your program a good value for */
/*               VERSN would be */

/*               'KINDLE --- Version 4.2.3' */

/*               Your greeting routine can make use of this when */
/*               displaying your program's greeting. In this way */
/*               you can centralize the name and version number of */
/*               your program at a high level or in a subroutine and */
/*               simply make the information available to TSETUP so */
/*               that the automatic aspects of presenting this */
/*               information can be handled for you. */

/* $ Detailed_Output */

/*     None. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     None. This routine cannot detect any errors in its inputs */
/*     and all commands are regarded as legal input at this level. */

/* $ Files */

/*     The file specified by LOGFIL will be opened if possible */
/*     and all test results will then be stored in that file. */

/*     Other files may be used a run time by "STARTing" a command */
/*     sequence file. Or by some result of the activity of the */
/*     user supplied routines ACTION, GREET, PREPRC. */

/* $ Particulars */

/*     This routine preforms the initializations needed for using */
/*     the NAIF test utilities. It should be called once in your */
/*     test program. */

/*     The routine process an input string, CMLINE, to determine any */
/*     run-time options. */

/* $ Examples */

/*     None. */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     W.L. Taber    (JPL) */

/* $ Version */

/* -     Test Utilities Version 2.0.0, 19-MAY-2010 (EDW) */

/*         Eliminated GETCML call from TSETUP. The command line */
/*         passes into TSETUP as an argument CMLINE. */

/*         The addition of the CMLINE argument nullifies the need to use */
/*         the "tspice.ker" kernel to pass command line arguments */
/*         in environments without shells, e.g IDL, Matlab. The code */
/*         implementing loading and processing of "tspice.ker" has */
/*         been removed. */

/* -     Test Utilities Version 1.3.0, 09-MAY-2002 (EDW) */

/*         Added capability to read command line options from */
/*         a text kernel. tspice checks for the existence of */
/*         the kernel "tspice.ker" if present, and if no arguments */
/*         supplied on the command line, tspice reads the */
/*         COMMAND_LINE string variable from the kernel then uses */
/*         that string as the command line. */

/* -     Test Utilities Version 1.2.0, 24-APR-2002 (EDW) */

/*         Added the quiet mode, activated from the command line */
/*         by the '-Q' argument. The mode prevents output to the */
/*         standard device, i.e. the screen. Modifications made to */
/*         tstio.f. */

/*         Moved command line parse code to a position so it executes */
/*         prior to logging functions. */

/* -     Test Utilities Version 1.1.0, 27-JUL-1999 (WLT) */

/*         Added initialization for automatic checks of SPICE */
/*         exception handling. Added "DEBUGGING" mode to Test Utilites. */

/* -     Test Utilities Version 1.0.0,  3-NOV-1994 (WLT) */

/* -& */

/*     Test Utility Functions */


/*     Local Variables */


/*     The following styles are for reporting errors to the */
/*     screen and log file respectively. */

    s_copy(sstyle, "HARDSPACE ^ NEWLINE /cr VTAB /vt FLAG Failure: ", (ftnlen)
	    128, (ftnlen)47);
    s_copy(lstyle, "HARDSPACE ^ NEWLINE /cr VTAB /vt FLAG Failure: LEADER --"
	    " LEFT 1 RIGHT 72 ", (ftnlen)128, (ftnlen)73);

/*     Set the exception handling status to OFF and set the debugging */
/*     status to OFF. */

    dummy = setoff_("CHCKXC", (ftnlen)6);
    dummy = setoff_("DEBUGGING", (ftnlen)9);

/*     The following styles will be used for logging of */
/*     commands and for commenting them out. */

    s_copy(vstyle, "LEFT 1 RIGHT 78 ", (ftnlen)128, (ftnlen)16);
    s_copy(hstyle, "LEFT 1 RIGHT 78 LEADER -- FLAG -- ", (ftnlen)128, (ftnlen)
	    34);
    tstlgs_(vstyle, hstyle, (ftnlen)128, (ftnlen)128);
    while(s_cmp(cmline, " ", cmline_len, (ftnlen)1) != 0) {
	nextwd_(cmline, word, cmline, cmline_len, (ftnlen)32, cmline_len);
	ucase_(word, word, (ftnlen)32, (ftnlen)32);
	if (s_cmp(word, "-V", (ftnlen)32, (ftnlen)2) == 0) {
	    on = verbon_();
	} else if (s_cmp(word, "-C", (ftnlen)32, (ftnlen)2) == 0) {
	    tstlcy_();
	} else if (s_cmp(word, "-D", (ftnlen)32, (ftnlen)2) == 0) {

/*           We want to run in debugging mode. This means */
/*           files are not automatically deleted when a new */
/*           test family is initiated. */

	    on = seton_("DEBUGGING", (ftnlen)9);
	}

/*        Check for quiet mode; supress all output to the */
/*        standard IO device. */

	if (s_cmp(word, "-Q", (ftnlen)32, (ftnlen)2) == 0) {
	    lckout_("SCREEN", (ftnlen)6);
	}
    }

/*     Open a log file. */

    tstopl_(lognam, versn, lognam_len, versn_len);

/*     Now, set up the SPICELIB error handling. */

    erract_("SET", "RETURN", (ftnlen)3, (ftnlen)6);
    errdev_("SET", "NULL", (ftnlen)3, (ftnlen)4);
    return 0;
} /* tsetup_ */

