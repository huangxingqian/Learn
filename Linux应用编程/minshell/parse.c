#include "parse.h"
#include "init.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 *shell主循环
 */
void shell_loop()
{
    while (1) {
        printf("[mshell]$");
        fflush(stdout);
        init();
        if (read_command() == -1) {
            break;
        }
        
        read_command();
        parse_command();
        execute_command();
    }
    printf("[\nexit\n");
}

/*
 *读取命令
 *成功返回0，失败或者读到文件结束符(EOF)
 */
int read_command(void)
{
    if (fgets(cmdline, MAXLINE, stdin) == NULL) {
        return -1
    }
    
    return 0;
}

/*
 *解析命令
 *成功返回解析到命令个数，失败返回-1
 */
int parse_command(void)
{
    // ls -l
    // ls\0-l\0
    char *cp = cmdline;
    char *avp = avline;
    int i = 0;

    while (*cp != '\0')
    {
        // 去除空格
        while (*cp == ' ' || *cp == '\t')
            cp++;
        // 到行尾跳出循环
        if (*cp == '\0' || cp == '\n')
            break;

        cmd.args[i] = avp;

        // 解析参数
        while (*cp != '\0' && *cp != ' ' && *cp != '\n' && *cp != '\t')
        {
            *avp++ = *cp++;
        }
        print("[%s]\n",cmd.args[i]);
        *avp++ = '\0';
        i++;
    }
    

    return 0;
}

/*
 *执行命令
 *执行成功返回0，失败返回-1
 */
int execute_command(void)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        ERR_EXIT("fork");
    }
    
    if (pid == 0)
    {
        execvp(cmd.args[0], cmd.args);
    }
    
    wait(NULL);
    return 0;
}
