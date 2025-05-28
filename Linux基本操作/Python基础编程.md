# Python编程基础

Python是一种高级、解释型、通用的编程语言，以其简洁易读的语法和强大的功能而广受欢迎。以下是Python编程的基础知识概览：

## 1. 基本语法

```python
# 这是单行注释

"""
这是多行注释
可以跨越多行
"""

print("Hello, World!")  # 输出语句
```

## 2. 变量和数据类型

```python
# 变量赋值
x = 10          # 整数
y = 3.14         # 浮点数
name = "Alice"   # 字符串
is_active = True # 布尔值

# 基本数据类型
print(type(x))        # <class 'int'>
print(type(y))        # <class 'float'>
print(type(name))     # <class 'str'>
print(type(is_active))# <class 'bool'>
```

## 3. 运算符

```python
# 算术运算符
a = 10 + 5   # 加
b = 10 - 5   # 减
c = 10 * 5   # 乘
d = 10 / 3   # 除
e = 10 // 3  # 整除
f = 10 % 3   # 取模
g = 2 ** 3   # 幂运算

# 比较运算符
print(10 > 5)   # True
print(10 == 5)  # False
print(10 != 5)  # True

# 逻辑运算符
print(True and False)  # False
print(True or False)   # True
print(not True)        # False
```

## 4. 控制结构

### 条件语句

```python
age = 18

if age < 18:
    print("未成年")
elif age == 18:
    print("刚成年")
else:
    print("成年")
```

### 循环结构

```python
# for循环
for i in range(5):  # 0到4
    print(i)

# while循环
count = 0
while count < 5:
    print(count)
    count += 1
```

## 5. 数据结构

### 列表(List)

```python
fruits = ["apple", "banana", "cherry"]
print(fruits[1])      # banana
fruits.append("orange") # 添加元素
print(len(fruits))    # 4
```

### 元组(Tuple)

```python
coordinates = (10.0, 20.0)
print(coordinates[0])  # 10.0
# coordinates[0] = 5.0 # 会报错，元组不可变
```

### 字典(Dictionary)

```python
person = {
    "name": "Alice",
    "age": 25,
    "is_student": True
}
print(person["name"])  # Alice
person["age"] = 26     # 修改值
```

### 集合(Set)

```python
unique_numbers = {1, 2, 3, 3, 4}
print(unique_numbers)  # {1, 2, 3, 4}
```

## 6. 函数

```python
def greet(name, greeting="Hello"):
    """这是一个简单的问候函数"""
    return f"{greeting}, {name}!"

print(greet("Alice"))          # Hello, Alice!
print(greet("Bob", "Hi"))      # Hi, Bob!
```

## 7. 文件操作

```python
# 写入文件
with open("example.txt", "w") as file:
    file.write("Hello, Python!")

# 读取文件
with open("example.txt", "r") as file:
    content = file.read()
    print(content)  # Hello, Python!
```

## 8. 异常处理

```python
try:
    result = 10 / 0
except ZeroDivisionError:
    print("不能除以零!")
finally:
    print("这段代码总会执行")
```

## 9. 面向对象编程

```python
class Dog:
    # 类属性
    species = "Canis familiaris"
    
    # 初始化方法
    def __init__(self, name, age):
        self.name = name  # 实例属性
        self.age = age
    
    # 实例方法
    def bark(self):
        return f"{self.name} says woof!"

# 创建实例
my_dog = Dog("Buddy", 5)
print(my_dog.bark())  # Buddy says woof!
```

## 10. 模块和包

```python
# 导入模块
import math
print(math.sqrt(16))  # 4.0

# 从模块导入特定函数
from random import randint
print(randint(1, 10))  # 随机1-10的数字
```

这只是Python编程的基础概述。Python还有更多高级特性，如生成器、装饰器、上下文管理器、多线程/多进程编程等，等待你去探索！