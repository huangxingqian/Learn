/*在Linux上编写一个c语言应用程序，程序实现创建一个文件，添加可读可写权限，对文件以1s一次进行写入，写入时打印线程id和写动作提示，有两个线程对这个文件进行写入操作，为这个文件添加写保护*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define FILENAME "shared_file.txt"
#define NUM_THREADS 2
#define WRITE_INTERVAL 1 // 1 second

// 文件描述符和互斥锁
int fd;
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

// 线程函数
void *write_to_file(void *threadid) {
    long tid = (long)threadid;
    char buffer[256];
    int count = 0;
    
    while (1) {
        // 准备要写入的内容
        snprintf(buffer, sizeof(buffer), 
                "Thread ID: %ld, Write count: %d, Timestamp: %ld\n", 
                tid, count++, time(NULL));
        
        // 加锁保护文件写入
        pthread_mutex_lock(&file_mutex);
        
        // 写入文件
        ssize_t bytes_written = write(fd, buffer, strlen(buffer));
        if (bytes_written == -1) {
            printf("Thread %ld: Write failed: %s\n", tid, strerror(errno));
        } else {
            printf("Thread %ld: Wrote %zd bytes to file\n", tid, bytes_written);
            // 确保数据写入磁盘
            fsync(fd);
        }
        
        // 解锁
        pthread_mutex_unlock(&file_mutex);
        
        // 等待1秒
        sleep(WRITE_INTERVAL);
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    
    // 创建文件并设置权限为可读可写 (rw-r--r--)
    fd = open(FILENAME, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    close(fd);
    
    printf("File created with read-write permissions\n");
    
    
    // 创建线程
    for (t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, write_to_file, (void *)t);
        if (rc) {
            printf("Error: unable to create thread, %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }
    
    // 等待线程结束 (实际上不会结束，因为线程是无限循环)
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }
    
    // 关闭文件 (实际上不会执行到这里)
    close(fd);
    
    return 0;
}