#include "init.h"
#include "externs.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>

void sigint_handlder(int sig);

/*
 *忽略SIGINT、SIGQUIT信号
 */
void setup(void)
{
    signal(SIGINT, sigint_handlder);
    signal(SIGQUIT, SIG_IGN);
}

void sigint_handlder(int sig)
{
    printf("\n[minshell]$ ");
    fflush(stdout);
}

void init()
{
    memset(&cmd, 0, sizeof(cmd));
    memset(&cmdline, 0, sizeof(cmdline));
}

