#include "parse.h"
#include "init.h"
#include "externs.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void get_command(int i);
int check(const char *str);
void getname(char *name);


/*
 *shell主循环
 */
void shell_loop()
{
    while (1) {
        printf("[minshell]$");
        fflush(stdout);
        init();
        if (read_command() == -1) {
            break;
        }

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
        return -1;
    }

    return 0;
}

/*
 *解析命令
 *成功返回解析到命令个数，失败返回-1
 */
int parse_command(void)
{
    // cat < text.txt | gerp -n > text2.txt &
    // 1.是否有指令
    // 2.解析第一个命令
    get_command(0);
    // 3.判断是否是输入重定向符
    if (check("<")) {
        getname(infile);
    }
    // 4.判断是否有管道
    int i;
    for (i = 0; i < PIPELINE; i++) {
        if (check("|")) {
            get_command(i);
        } else 
        {
            break;
        }
    }
    // 5.判断是否有输出重定向符
    if (check(">")) {
        getname(outfile);
    }
    // 6.是否是后台作业
    if (check("&")) {
        backgnd = 1;
    }
    // 7.判断命令是否结束
    if (check("\n")) {
        cmd_count = i;
        retuen cmd_count;
    } else {
        fprintf(stderr, "Command line syntax error");
        return -1;
    }
    return 0;
}

/*
 *执行命令
 *执行成功返回0，失败返回-1
 */
int execute_command(void)
{
    /*
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
    */
    return 0;
}
/*
 * 解析简单命令到cmd[i]
 * 解析命令参数cmdline到avline数组中
 * 并且将COMMAND结构体中args[]
 */
void get_command(int i)
{
    int j = 0;
    int inword;
    while (*lineptr != '\0') {
        // 去除空格
        while (*lineptr == ' ' || *lineptr == '\t') {
            *lineptr++;
        }
        cmd[i].args[j] = avptr;
        while(*lineptr 
            != '\0' && *lineptr != '\t' && *lineptr != '>' && *lineptr != '<' && *lineptr != '|' && *lineptr != '&'
        ) {
            *avptr++ = *lineptr++;
            inword = 1;
        }
        *avptr++ = '\0';
        switch (*lineptr) {
            case ' ':
            case '\t':
                inword = 0;
                j++
                break;
            case '<':
            case '>':
            case '|':
            case '&':
            case '\n':
                if (inword == 0) {
                    cmd[i].args[j] == NULL;
                }
                return;
            
            default:
                return;
        }
    }
}

int check(const char *str)
{
    
}

void getname(char *name)
{
    
}
