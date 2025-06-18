# System V IPC 函数详解

System V IPC 是 Unix/Linux 系统中经典的进程间通信机制，主要包括三种类型：**共享内存**、**消息队列** 和 **信号量**。下面我将详细解释这三种机制的相关函数。

## 1. 共享内存 (Shared Memory)

共享内存允许多个进程共享同一块内存区域，是最快的IPC方式。

### 主要函数

#### `shmget()` - 创建/获取共享内存段
```c
#include <sys/ipc.h>
#include <sys/shm.h>

int shmget(key_t key, size_t size, int shmflg);
```
- **参数**:
  - `key`: 共享内存键值，通常使用`ftok()`生成或`IPC_PRIVATE`
  - `size`: 共享内存段大小(字节)
  - `shmflg`: 权限标志(如`IPC_CREAT | 0666`)
- **返回值**: 成功返回共享内存标识符，失败返回-1

#### `shmat()` - 附加共享内存段
```c
void *shmat(int shmid, const void *shmaddr, int shmflg);
```
- **参数**:
  - `shmid`: `shmget()`返回的标识符
  - `shmaddr`: 指定附加地址(通常为NULL让系统选择)
  - `shmflg`: 附加标志(如`SHM_RDONLY`只读附加)
- **返回值**: 成功返回共享内存段地址，失败返回`(void *)-1`

#### `shmdt()` - 分离共享内存段
```c
int shmdt(const void *shmaddr);
```
- **参数**: `shmat()`返回的地址
- **返回值**: 成功返回0，失败返回-1

#### `shmctl()` - 控制共享内存段
```c
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```
- **参数**:
  - `shmid`: 共享内存标识符
  - `cmd`: 控制命令(如`IPC_RMID`删除)
  - `buf`: 指向`shmid_ds`结构的指针
- **返回值**: 成功返回0，失败返回-1

### 示例代码
```c
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
    
    char *str = (char*)shmat(shmid, NULL, 0);
    sprintf(str, "Hello Shared Memory");
    printf("Data written in memory: %s\n", str);
    
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
```

## 2. 消息队列 (Message Queues)

消息队列允许进程以消息形式交换数据。

### 主要函数

#### `msgget()` - 创建/获取消息队列
```c
#include <sys/ipc.h>
#include <sys/msg.h>

int msgget(key_t key, int msgflg);
```
- **参数**:
  - `key`: 消息队列键值
  - `msgflg`: 权限标志
- **返回值**: 成功返回消息队列标识符，失败返回-1

#### `msgsnd()` - 发送消息
```c
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
```
- **参数**:
  - `msqid`: 消息队列标识符
  - `msgp`: 指向消息结构的指针
  - `msgsz`: 消息正文大小(不包括消息类型)
  - `msgflg`: 标志(如`IPC_NOWAIT`)

#### `msgrcv()` - 接收消息
```c
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
```
- **参数**:
  - `msgtyp`: 0表示接收第一条消息，>0表示接收指定类型的消息

#### `msgctl()` - 控制消息队列
```c
int msgctl(int msqid, int cmd, struct msqid_ds *buf);
```

### 示例代码
```c
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666|IPC_CREAT);
    
    // 发送消息
    message.msg_type = 1;
    sprintf(message.msg_text, "Hello Message Queue");
    msgsnd(msgid, &message, sizeof(message), 0);
    
    // 接收消息
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Data received: %s\n", message.msg_text);
    
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
```

## 3. 信号量 (Semaphores)

信号量用于进程间的同步。

### 主要函数

#### `semget()` - 创建/获取信号量集
```c
#include <sys/ipc.h>
#include <sys/sem.h>

int semget(key_t key, int nsems, int semflg);
```
- **参数**:
  - `nsems`: 信号量集中信号量的数量

#### `semop()` - 信号量操作
```c
int semop(int semid, struct sembuf *sops, size_t nsops);
```
- **参数**:
  - `sops`: 指向操作数组的指针
  - `nsops`: 操作数组中操作的数量

#### `semctl()` - 控制信号量
```c
int semctl(int semid, int semnum, int cmd, ...);
```
- **常用cmd**:
  - `SETVAL`: 设置信号量的值
  - `IPC_RMID`: 删除信号量集

### 示例代码
```c
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t key = ftok("semfile", 65);
    int semid = semget(key, 1, 0666|IPC_CREAT);
    
    union semun arg;
    arg.val = 1;  // 初始值为1
    semctl(semid, 0, SETVAL, arg);
    
    struct sembuf sb = {0, -1, 0};  // P操作
    semop(semid, &sb, 1);
    printf("Critical section start\n");
    sleep(5);  // 模拟临界区操作
    printf("Critical section end\n");
    
    sb.sem_op = 1;  // V操作
    semop(semid, &sb, 1);
    
    semctl(semid, 0, IPC_RMID);
    return 0;
}
```

## 通用函数

### `ftok()` - 生成IPC键值
```c
key_t ftok(const char *pathname, int proj_id);
```
- **参数**:
  - `pathname`: 存在的文件路径
  - `proj_id`: 项目ID(1-255)
- **返回值**: 生成的键值

## 注意事项

1. 所有System V IPC资源都是持久的，除非显式删除或系统重启
2. 使用`ipcs`命令查看IPC资源，`ipcrm`删除资源
3. 需要包含头文件`<sys/ipc.h>`和`<sys/shm.h>`(或`<sys/msg.h>`/`<sys/sem.h>`)
4. 在多线程环境中使用需要额外注意同步问题

System V IPC虽然功能强大，但在现代编程中，POSIX IPC(如`shm_open()`、`mq_open()`等)通常是更好的选择，因为它们设计更简洁，接口更一致。