#ifndef _DEF_H_
#define _DEF_H_
#include <stdio.h>
#include <stdlib.h>

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while (0)


#define MAXLINE 1024    //输入行最大长度
#define MAXARG 20       //参数最大个数
#define PIPELINE 5      //一个管道行中简单命令的最多个数
#define MAXNAME 100     //IO重定向文件名的最大长度

typedef struct command
{
    char *args[MAXARG+1]; //解析出的命令字符参数列表
    int infd;
    int outfd;
} COMMAND;

#endif