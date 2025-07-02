#ifndef _EXTERND_H_
#define _EXTERND_H_
#include "def.h"

extern char cmdline[MAXLINE+1];
extern char avline[MAXLINE+1];
extern COMMAND cmd[PIPELINE];
extern char infile[MAXNAME+1];
extern char outfile[MAXNAME+1];

extern int cmd_count；
extern int backgnd;
extern char *lineptr;
extern char *avptr;
#endif
