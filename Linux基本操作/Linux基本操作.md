   - `/`：根目录（所有目录的起点）
   - `~`：当前用户的家目录（如 `/home/username`）
   - `.`：当前目录
   - `..`：上级目录
2. **常用命令**
   - **`pwd`**：显示当前所在目录的路径。
   - **`ls`**：列出目录内容。
     ```bash
     ls -l  # 显示详细信息（权限、大小等）
     ls -a  # 显示隐藏文件（以`.`开头）
     ```
   - **`cd`**：切换目录。
     ```bash
     cd /path/to/dir  # 进入绝对路径
     cd ..            # 返回上级目录
     cd ~             # 返回家目录
     ```
   - **`mkdir`**：创建目录。
     ```bash
     mkdir new_dir         # 创建空目录
     mkdir -p dir1/dir2    # 递归创建多级目录
     ```
   - **`touch`**：创建空文件或更新文件时间戳。
     ```bash
     touch file.txt
     ```
   - **`cp`**：复制文件/目录。
     ```bash
     cp file.txt new_file.txt        # 复制文件
     cp -r dir1 dir2                 # 递归复制目录
     ```
   - **`mv`**：移动或重命名文件/目录。
     ```bash
     mv old.txt new.txt       # 重命名文件
     mv file.txt /target/dir  # 移动文件
     ```
   - **`rm`**：删除文件/目录（谨慎使用！）。
     ```bash
     rm file.txt             # 删除文件
     rm -r dir               # 递归删除目录（危险！）
     ```
   - **`cat`**：查看文件内容。
   - **`less`** 或 **`more`**：分页查看长文件（按 `q` 退出）。
   - **`head`** 和 **`tail`**：查看文件头部/尾部内容。
     ```bash
     tail -f log.txt  # 实时追踪日志文件
     ```
---
### **二、文件权限管理**
1. **查看权限**
   - 使用 `ls -l` 显示权限，格式如：`-rwxr-xr--`
   - 权限分为三组：所有者（user）、所属组（group）、其他用户（others）。
2. **修改权限**
   - **`chmod`**：修改文件权限。
     ```bash
     chmod 755 file.txt      # 数字模式（7=rwx, 5=r-x）
     chmod u+x script.sh     # 符号模式：给所有者添加执行权限
     ```
   - **`chown`**：修改文件所有者。
     ```bash
     chown user:group file.txt
     ```
---
### **三、文本处理**
1. **`grep`**：搜索文本。
   ```bash
   grep "keyword" file.txt      # 搜索文件中包含关键词的行
   grep -i "error" log.txt      # 忽略大小写搜索
   ```
2. **`sed`**：流编辑器（替换文本）。
   ```bash
   sed 's/old/new/g' file.txt   # 将文件中的 old 替换为 new
   ```
3. **`awk`**：文本分析工具。
   ```bash
   awk '{print $1}' file.txt    # 打印文件第一列
   ```
---
### **四、进程管理**
1. **`ps`**：查看进程状态。
   ```bash
   ps aux       # 显示所有进程详细信息
   ```
2. **`top`** 或 **`htop`**：实时监控系统资源。
3. **`kill`**：终止进程。
   ```bash
   kill -9 PID  # 强制终止指定PID的进程
   ```
---
### **五、软件包管理**
1. **Debian/Ubuntu（APT）**
   ```bash
   sudo apt update          # 更新软件源
   sudo apt install package # 安装软件包
   sudo apt remove package  # 卸载软件包
   ```
2. **CentOS/RHEL（YUM/DNF）**
   ```bash
   sudo yum install package
   sudo dnf remove package
   ```
---
### **六、压缩与解压**
1. **`tar`**：打包/解包文件。
   ```bash
   tar -czvf archive.tar.gz dir/   # 压缩为 .tar.gz
   tar -xzvf archive.tar.gz        # 解压 .tar.gz
   ```
2. **`zip`** 和 **`unzip`**：
   ```bash
   zip -r archive.zip dir/
   unzip archive.zip
   ```
---
### **七、网络操作**
1. **`ping`**：测试网络连通性。
   ```bash
   ping example.com
   ```
2. **`curl`** 或 **`wget`**：下载文件。
   ```bash
   curl -O https://example.com/file.zip
   wget https://example.com/file.zip
   ```
3. **`ssh`**：远程登录。
   ```bash
   ssh user@hostname
   ```
---
### **八、实用技巧**
1. **重定向与管道**
   ```bash
   ls > list.txt        # 输出重定向到文件
   cat file.txt | grep "key"  # 管道传递结果
   ```
2. **历史命令**
   - 按 `↑`/`↓` 查看历史命令。
   - **`history`**：显示所有历史命令。
3. **Tab 补全**：输入部分命令或文件名后按 `Tab` 自动补全。
---
### **九、帮助命令**
- **`man`**：查看命令手册（如 `man ls`）。
- **`--help`**：快速查看命令帮助（如 `ls --help`）。
---
**注意事项**：
1. Linux 区分大小写（`File.txt` 和 `file.txt` 是不同文件）。
2. 慎用 `rm -rf /` 或 `rm -rf *`，可能导致数据丢失！
3. 使用 `sudo` 执行需要管理员权限的命令。
掌握以上操作后，你可以进一步学习 Shell 脚本、系统服务管理等进阶内容。
3. 使用 `sudo` 执行需要管理员权限的命令。
掌握以上操作后，你可以进一步学习 Shell 脚本、系统服务管理等进阶内容。