# Shell脚本使用指导

Shell脚本是Linux/Unix系统中强大的自动化工具，下面是一份基础使用指南：

## 1. 创建和运行脚本

```bash
#!/bin/bash
# 这是一个注释
echo "Hello World!"
```

- 第一行`#!/bin/bash`称为shebang，指定解释器
- 保存为`.sh`文件，例如`myscript.sh`
- 运行前需要添加执行权限：`chmod +x myscript.sh`
- 运行方式：
  - `./myscript.sh`
  - `bash myscript.sh`
  - `source myscript.sh` (在当前shell环境执行)

## 2. 基本语法

### 变量
```bash
name="John"      # 定义变量
echo $name       # 使用变量
echo ${name}     # 推荐使用花括号
readonly var     # 只读变量
unset var        # 删除变量
```

### 特殊变量
```bash
$0       # 脚本名称
$1-$9    # 脚本参数
$#       # 参数个数
$*       # 所有参数
$?       # 上条命令的退出状态
$$       # 当前脚本的进程ID
```

## 3. 条件判断

```bash
if [ condition ]; then
  # 代码
elif [ condition ]; then
  # 代码
else
  # 代码
fi
```

常用测试条件：
- 字符串比较：`=`, `!=`, `-z`(空), `-n`(非空)
- 数字比较：`-eq`, `-ne`, `-gt`, `-lt`, `-ge`, `-le`
- 文件测试：`-e`(存在), `-f`(是文件), `-d`(是目录), `-r`(可读), `-w`(可写), `-x`(可执行)

## 4. 循环结构

### for循环
```bash
for var in item1 item2 ... itemN; do
  # 代码
done

# C风格for循环
for ((i=0; i<10; i++)); do
  echo $i
done
```

### while循环
```bash
while [ condition ]; do
  # 代码
done
```

### until循环
```bash
until [ condition ]; do
  # 代码
done
```

## 5. 函数

```bash
function_name() {
  # 函数体
  return value  # 可选
}

# 调用函数
function_name arg1 arg2
```

## 6. 实用技巧

- 命令替换：`` `command` `` 或 `$(command)`
- 算术运算：`$((expression))`
- 调试模式：`bash -x script.sh`
- 检查语法：`bash -n script.sh`
- 获取选项参数：使用`getopts`

## 7. 常用命令

- `echo`：输出文本
- `printf`：格式化输出
- `read`：读取用户输入
- `test`/[ ]：条件测试
- `exit`：退出脚本
- `shift`：移动位置参数

## 示例脚本

```bash
#!/bin/bash

# 显示欢迎信息
echo "系统信息:"
echo "主机名: $(hostname)"
echo "当前用户: $(whoami)"
echo "日期: $(date)"

# 检查文件是否存在
if [ -f "/etc/passwd" ]; then
  echo "/etc/passwd 文件存在"
else
  echo "/etc/passwd 文件不存在"
fi

# 处理参数
echo "脚本名称: $0"
echo "第一个参数: $1"
echo "参数总数: $#"

# 循环示例
for i in {1..5}; do
  echo "迭代 $i"
done
```

要成为Shell脚本高手，建议多练习实际案例，并学习`grep`、`awk`、`sed`等文本处理工具的组合使用。
# Shell脚本详细使用指南

Shell脚本是Linux/Unix系统中强大的自动化工具，下面我将详细介绍其使用方法，包括基础语法、高级特性和实用技巧。

## 一、脚本基础

### 1. 创建与执行
```bash
#!/bin/bash
# 注释：第一行指定解释器
echo "Hello World!"  # 打印语句

# 保存为test.sh后
chmod +x test.sh     # 添加执行权限
./test.sh            # 执行方式1
bash test.sh         # 执行方式2
source test.sh       # 在当前shell执行
```

### 2. 变量操作
```bash
var="value"                  # 定义变量
echo ${var}                  # 使用变量
readonly CONST="immutable"   # 只读变量
unset var                    # 删除变量

# 特殊变量
echo "脚本名: $0"            # 脚本名称
echo "第一个参数: $1"        # 位置参数
echo "参数个数: $#"          # 参数数量
echo "所有参数: $@"          # 全部参数
echo "上条命令状态: $?"      # 退出状态
echo "当前进程ID: $$"        # 进程ID
```

## 二、字符串处理

### 1. 基本操作
```bash
str="Hello World"
echo ${#str}            # 字符串长度(11)
echo ${str:0:5}         # 子串(Hello)
echo ${str/World/Shell} # 替换(Hello Shell)

# 连接字符串
str1="Hello"
str2="World"
result=$str1$str2
```

### 2. 字符串判断
```bash
if [ -z "$str" ]; then   # 是否为空
  echo "字符串为空"
elif [ -n "$str" ]; then # 是否非空
  echo "字符串非空"
fi

if [[ $str == "Hello" ]]; then  # 字符串比较
  echo "匹配成功"
fi
```

## 三、数组操作

### 1. 定义与访问
```bash
arr=("a" "b" "c")       # 定义数组
echo ${arr[1]}          # 访问元素(b)
arr[3]="d"              # 添加元素

# 特殊操作
echo ${arr[@]}          # 所有元素
echo ${#arr[@]}         # 数组长度
```

### 2. 数组遍历
```bash
for i in "${arr[@]}"; do
  echo $i
done

# C风格遍历
for ((i=0; i<${#arr[@]}; i++)); do
  echo ${arr[$i]}
done
```

## 四、条件判断

### 1. 基本语法
```bash
if [ condition ]; then
  # 代码块
elif [ condition ]; then
  # 代码块
else
  # 代码块
fi
```

### 2. 测试条件
```bash
# 文件测试
[ -e file ]    # 存在
[ -f file ]    # 是普通文件
[ -d dir ]     # 是目录
[ -r file ]    # 可读
[ -w file ]    # 可写
[ -x file ]    # 可执行

# 数值比较
[ $a -eq $b ]  # 等于
[ $a -ne $b ]  # 不等于
[ $a -gt $b ]  # 大于
[ $a -lt $b ]  # 小于

# 字符串比较
[ "$a" = "$b" ]  # 等于
[ "$a" != "$b" ] # 不等于
```

## 五、循环结构

### 1. for循环
```bash
# 列表循环
for i in 1 2 3 4 5; do
  echo $i
done

# 范围循环
for i in {1..5}; do
  echo $i
done

# C风格循环
for ((i=0; i<5; i++)); do
  echo $i
done
```

### 2. while循环
```bash
count=1
while [ $count -le 5 ]; do
  echo $count
  ((count++))
done

# 读取文件行
while read line; do
  echo $line
done < file.txt
```

### 3. until循环
```bash
count=1
until [ $count -gt 5 ]; do
  echo $count
  ((count++))
done
```

## 六、函数使用

### 1. 定义与调用
```bash
# 定义函数
greet() {
  local name=$1  # 局部变量
  echo "Hello, $name"
  return 0       # 返回值
}

# 调用函数
greet "Alice"
echo "返回值: $?"  # 获取返回值
```

### 2. 参数传递
```bash
func() {
  echo "第一个参数: $1"
  echo "第二个参数: $2"
  echo "所有参数: $@"
}

func "a" "b" "c"
```

## 七、高级特性

### 1. 信号处理
```bash
trap "echo '捕获中断信号'; exit" SIGINT

# 常见信号:
# SIGINT (2) - Ctrl+C
# SIGTERM (15) - 终止信号
# SIGKILL (9) - 强制终止(不可捕获)
```

### 2. 子shell与进程
```bash
(cd /tmp && ls)  # 子shell中执行，不影响当前shell

# 后台执行
command &

# 获取命令输出
output=$(command)
```

### 3. 正则表达式
```bash
if [[ "string" =~ ^s.*g$ ]]; then
  echo "正则匹配成功"
fi
```

## 八、调试技巧

### 1. 调试模式
```bash
bash -x script.sh  # 显示执行过程
bash -n script.sh  # 只检查语法不执行
```

### 2. 调试语句
```bash
set -x   # 开启调试
# 代码块
set +x   # 关闭调试

# 输出调试信息
echo "Debug: var=$var" >&2  # 输出到标准错误
```

## 九、实用示例

### 1. 备份脚本
```bash
#!/bin/bash
# 简单备份脚本

BACKUP_DIR="/backup"
DATE=$(date +%Y%m%d)
TARGET_DIRS=("/etc" "/home" "/var/www")

mkdir -p $BACKUP_DIR/$DATE

for dir in "${TARGET_DIRS[@]}"; do
  name=$(basename $dir)
  tar -czf "$BACKUP_DIR/$DATE/$name.tar.gz" "$dir"
done

echo "备份完成于 $(date)" >> $BACKUP_DIR/backup.log
```

### 2. 系统监控
```bash
#!/bin/bash
# 系统资源监控

while true; do
  clear
  echo "===== 系统监控 ====="
  echo "时间: $(date)"
  echo "CPU使用: $(top -bn1 | grep load | awk '{printf "%.2f%%\n", $(NF-2)}')"
  echo "内存使用: $(free -m | awk '/Mem/{printf "%.2f%%\n", $3/$2*100}')"
  echo "磁盘空间: $(df -h / | awk '/\//{print $5}')"
  sleep 5
done
```

掌握这些Shell脚本技术后，你可以：
1. 自动化日常系统管理任务
2. 处理日志文件和分析数据
3. 创建复杂的部署脚本
4. 构建自定义系统工具

建议从简单脚本开始，逐步增加复杂度，实践中学习更多高级技巧。 