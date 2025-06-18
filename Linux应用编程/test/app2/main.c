/*在Linux上编写一个c语言应用程序，程序实现使用内存映射函数，完成父子进程通信功能*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

#define SHARED_SIZE 4096  // 共享内存大小

int main() {
    // 1. 创建共享内存区域
    void *shared_memory = mmap(NULL, SHARED_SIZE, 
                              PROT_READ | PROT_WRITE,
                              MAP_SHARED | MAP_ANONYMOUS, 
                              -1, 0);
    
    if (shared_memory == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory created at %p\n", shared_memory);

    // 2. 创建子进程
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // 父进程
        printf("Parent process (PID: %d)\n", getpid());
        
        // 写入消息到共享内存
        const char *message = "Hello from parent!";
        strncpy((char *)shared_memory, message, SHARED_SIZE);
        printf("Parent wrote: %s\n", message);

        // 等待子进程读取并回复
        sleep(1);
        
        // 读取子进程的回复
        printf("Parent received: %s\n", (char *)shared_memory);

        // 等待子进程结束
        wait(NULL);
        
        // 解除内存映射
        munmap(shared_memory, SHARED_SIZE);
    } 
    else {  // 子进程
        printf("Child process (PID: %d)\n", getpid());
        
        // 等待父进程写入数据
        sleep(1);
        
        // 读取父进程的消息
        printf("Child received: %s\n", (char *)shared_memory);
        
        // 回复消息
        const char *reply = "Hello from child!";
        strncpy((char *)shared_memory, reply, SHARED_SIZE);
        printf("Child replied: %s\n", reply);
    }

    return 0;
}