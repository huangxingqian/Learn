# gdb使用方法
### 一、基本调试流程
1. 启动调试
    - 调试未运行程序：
      ```bash
gdb ./your_program  # 加载可执行文件
```
    - 附加到正在运行的进程：
      ```bash
gdb attach <PID>    # 替换为进程的实际ID
```
    - 带参数启动程序：
      ```bash
gdb --args ./your_program arg1 arg2  # 传递运行参数
```
2. 设置断点
    - 按行号或函数名设置：
      ```bash
(gdb) break main       # 在main函数入口设断点
(gdb) break filename.c:20  # 指定文件的第20行
```
    - 条件断点：
      ```bash
(gdb) break 15 if x > 5  # 当变量x>5时触发
```
3. 运行程序
  ```bash
(gdb) run          # 启动程序直到遇到断点
(gdb) continue     # 继续运行到下一个断点或结束
```
4. 单步调试
    - next（缩写n）：逐行执行，不进入函数内部。
    - step（缩写s）：进入函数内部逐行调试。
    - finish：执行完当前函数并跳出。
---
### 二、数据查看与修改
1. 查看变量值
  ```bash
(gdb) print x      # 显示变量x的值
(gdb) display x    # 每次暂停自动显示x的值
```
2. 查看内存与寄存器
  ```bash
(gdb) x/10x &array  # 查看数组前10个元素的十六进制值
(gdb) info registers  # 显示寄存器内容
```
3. 修改变量值
  ```bash
(gdb) set variable x = 42  # 修改变量x的值为42
```
4. 调用栈分析
  ```bash
(gdb) backtrace     # 查看函数调用栈（缩写`bt`）
```
---
### 三、高级调试技巧
1. 观察点（Watchpoint）
  ```bash
(gdb) watch x       # 当x的值变化时暂停程序
```
2. 多线程调试
  ```bash
(gdb) info threads  # 查看所有线程状态
(gdb) thread 2      # 切换到线程2
```
3. 脚本化调试
  ```bash
gdb -x commands.gdb ./your_program  # 通过脚本执行预设命令
```
4. 远程调试
适用于嵌入式系统，需配合gdbserver工具实现跨机器调试。
---
### 四、常见问题排查示例
示例：段错误调试
1. 编译时添加调试信息：
  ```bash
gcc -g -o test test.c
```
2. 运行GDB定位错误：
  ```bash
(gdb) run
(gdb) where         # 查看崩溃时的调用栈
(gdb) list          # 显示崩溃点附近代码
(gdb) print *ptr    # 检查指针是否非法访问
```
---
### 五、注意事项
1. 编译选项：必须使用-g生成调试信息，避免使用优化选项（如-O2）。
2. 断点管理：合理设置条件断点减少干扰，使用info breakpoints查看所有断点。
3. 环境一致性：调试环境需与实际运行环境一致（如动态库路径）。
---
通过以上方法，可覆盖从基础到进阶的GDB调试需求。如需更深入的功能（如反汇编、信号处理），可通过help命令或查阅手册（man gdb）进一步探索。