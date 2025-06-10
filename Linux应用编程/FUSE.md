在 C 语言中使用 FUSE（Filesystem in Userspace）开发文件系统，通常需要借助 **libfuse** 库（或 **fuse3**）。下面详细介绍 FUSE 的核心函数、使用方法及完整示例。

---

## **1. 安装 FUSE 开发库**
在 Linux 上安装 `libfuse-dev`（或 `fuse3-devel`）：
```bash
# Debian/Ubuntu
sudo apt install libfuse3-dev

# RHEL/CentOS
sudo yum install fuse3-devel

# Arch Linux
sudo pacman -S fuse3
```

---

## **2. FUSE 的核心函数**
FUSE 文件系统的核心是定义一组回调函数（`struct fuse_operations`），由 FUSE 内核模块在文件操作时调用。主要函数包括：

| 函数名         | 作用                          | 对应系统调用       |
|----------------|-----------------------------|------------------|
| `getattr`      | 获取文件属性（如 `stat`）      | `stat()`         |
| `readdir`      | 读取目录内容                   | `readdir()`      |
| `open`         | 打开文件                      | `open()`         |
| `read`         | 读取文件内容                   | `read()`         |
| `write`        | 写入文件内容                   | `write()`        |
| `mkdir`        | 创建目录                      | `mkdir()`        |
| `unlink`       | 删除文件                      | `unlink()`       |
| `rmdir`        | 删除目录                      | `rmdir()`        |
| `create`       | 创建文件                      | `creat()`        |

---

## **3. 基本代码框架**
### **（1）定义 `fuse_operations` 结构体**
```c
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

static struct fuse_operations myfs_oper = {
    .getattr = myfs_getattr,
    .readdir = myfs_readdir,
    .open    = myfs_open,
    .read    = myfs_read,
};
```

### **（2）实现核心回调函数**
#### **`getattr` - 获取文件属性**
```c
static int myfs_getattr(const char *path, struct stat *stbuf) {
    memset(stbuf, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0) {  // 根目录
        stbuf->st_mode = S_IFDIR | 0755;  // 目录权限
        stbuf->st_nlink = 2;
    } else if (strcmp(path, "/hello.txt") == 0) {  // 文件
        stbuf->st_mode = S_IFREG | 0644;  // 文件权限
        stbuf->st_nlink = 1;
        stbuf->st_size = 12;  // 文件大小（"Hello World" 的长度）
    } else {
        return -ENOENT;  // 文件不存在
    }
    return 0;
}
```

#### **`readdir` - 读取目录内容**
```c
static int myfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                        off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    if (strcmp(path, "/") != 0)  // 只支持根目录
        return -ENOENT;

    filler(buf, ".", NULL, 0);   // 当前目录
    filler(buf, "..", NULL, 0);  // 上级目录
    filler(buf, "hello.txt", NULL, 0);  // 文件
    return 0;
}
```

#### **`open` - 打开文件**
```c
static int myfs_open(const char *path, struct fuse_file_info *fi) {
    if (strcmp(path, "/hello.txt") != 0)
        return -ENOENT;

    if ((fi->flags & O_ACCMODE) != O_RDONLY)  // 只读
        return -EACCES;

    return 0;
}
```

#### **`read` - 读取文件内容**
```c
static int myfs_read(const char *path, char *buf, size_t size, off_t offset,
                     struct fuse_file_info *fi) {
    (void) fi;

    if (strcmp(path, "/hello.txt") != 0)
        return -ENOENT;

    const char *content = "Hello World\n";
    size_t len = strlen(content);

    if (offset >= len)
        return 0;

    if (offset + size > len)
        size = len - offset;

    memcpy(buf, content + offset, size);
    return size;
}
```

---

### **（3）主函数 `main`**
```c
int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &myfs_oper, NULL);
}
```

---

## **4. 编译与运行**
### **（1）编译**
```bash
gcc -o myfs myfs.c `pkg-config fuse3 --cflags --libs`
```
（如果使用 `fuse2`，替换 `fuse3` 为 `fuse`）

### **（2）挂载文件系统**
```bash
mkdir /mnt/myfs
./myfs /mnt/myfs  # 默认前台运行（调试用）
```
（按 `Ctrl+C` 卸载）

### **（3）测试**
```bash
ls /mnt/myfs      # 查看目录
cat /mnt/myfs/hello.txt  # 读取文件
```

---

## **5. 高级用法**
### **（1）挂载选项**
```c
int main(int argc, char *argv[]) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    // 添加挂载选项，如 "-o allow_other"（允许其他用户访问）
    fuse_opt_add_arg(&args, "-oallow_other");
    return fuse_main(args.argc, args.argv, &myfs_oper, NULL);
}
```
运行：
```bash
./myfs -o allow_other /mnt/myfs
```

### **（2）调试模式**
```bash
./myfs -d /mnt/myfs  # 启用 FUSE 调试输出
```
或：
```bash
./myfs -f /mnt/myfs  # 前台运行（不守护进程）
```

---

## **6. 实际应用示例**
### **（1）实现内存文件系统**
在内存中维护文件结构（如哈希表或链表），动态响应读写操作。

### **（2）挂载 ZIP 文件**
类似 `fuse-zip`，解析 ZIP 文件结构，通过 FUSE 提供文件访问。

### **（3）加密文件系统**
在 `read`/`write` 中嵌入加密/解密逻辑（如 AES）。

---

## **7. 总结**
- **FUSE C API** 围绕 `struct fuse_operations` 实现回调。
- **核心函数**：`getattr`、`readdir`、`open`、`read`、`write` 等。
- **编译**：使用 `pkg-config` 链接 `libfuse3`。
- **调试**：`-d` 或 `-f` 选项查看详细日志。

通过 FUSE，你可以轻松实现各种虚拟文件系统，而无需编写内核模块！