#include "parse.h"
#include "init.h"
#include "def.h"
#include "externs.h"

char cmdline[MAXLINE+1];
char avline[MAXLINE+1];
COMMAND cmd[PIPELINE];
char infile[MAXNAME+1];
char outfile[MAXNAME+1];

int cmd_count；
int backgnd;
char *lineptr;
char *avptr;
int main(int argc,char* argv[])
{
    setup();
    shell_loop();
    return 0;
}