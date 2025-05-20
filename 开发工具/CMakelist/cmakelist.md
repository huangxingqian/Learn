# Cmakelist的使用方法
### 一、基本结构
1. 版本与项目定义
    - 指定CMake最低版本要求：
        ```cmake
        cmake_minimum_required(VERSION 3.10)  # 兼容性保障
        ```
    - 定义项目名称及版本：
        ```cmake
        project(MyProject VERSION 1.0 LANGUAGES CXX)  # 支持C++，可选版本号
        ```
2. 编译标准与参数
    - 设置C/C++标准：
        ```cmake
        set(CMAKE_CXX_STANDARD 17)  # 强制使用C++17
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        ```
    - 添加编译选项：
        ```cmake
        add_compile_options(-Wall -Wextra)  # 启用警告
        ```
3. 生成可执行文件与库
    - 添加可执行文件：
        ```cmake
        add_executable(MyApp main.cpp utils.cpp)  # 直接指定源文件
        ```
    - 生成静态/动态库：
        ```cmake
        add_library(MyLibrary STATIC src/mylib.cpp)  # 静态库
        add_library(MySharedLib SHARED src/shared.cpp)  # 动态库
        ```
---
### 二、多文件与目录管理
1. 包含头文件与链接库
    - 添加头文件路径：
        ```cmake
        include_directories(${PROJECT_SOURCE_DIR}/include)  # 全局包含
        target_include_directories(MyApp PRIVATE include)  # 仅目标包含
        ```
    - 链接库文件：
        ```cmake
        target_link_libraries(MyApp PRIVATE MyLibrary)  # 私有链接
        ```
2. 子目录管理
    - 递归编译子目录：
        ```cmake
        add_subdirectory(src)  # 自动调用子目录的CMakeLists.txt
        ```
3. 动态收集源文件
    - 使用通配符或函数：
        ```cmake
        file(GLOB SOURCES "src/*.cpp")  # 自动匹配源文件
        ```
---
### 三、高级用法
1. 条件编译与平台适配
    - 操作系统判断：
        ```cmake
        if(WIN32)
            add_definitions(-DWINDOWS)  # 定义Windows宏
        elseif(UNIX)
            target_link_libraries(MyApp pthread)  # Linux链接线程库
        endif()
        ```
2. 依赖管理与外部库
    - 查找并链接第三方库：
        ```cmake
        find_package(OpenCV REQUIRED)  # 查找OpenCV
        target_link_libraries(MyApp ${OpenCV_LIBS})
        ```
---
### 四、构建与调试
1. 外部构建流程
    - 推荐使用独立构建目录：
        ```bash
        mkdir build && cd build
        cmake ..  # 生成Makefile或项目文件
        make -j4   # 并行编译（4线程）
        ```
2. 调试信息与优化
    - 启用调试符号：
        ```cmake
        set(CMAKE_BUILD_TYPE Debug)  # 默认Release可改为Debug
        ```
3. 自定义命令与脚本
    - 集成预处理脚本：
        ```cmake
        add_custom_command(
            OUTPUT generated.cpp
            COMMAND python generate.py  # 生成代码
            DEPENDS generate.py
        )
        ```
---
### 五、常见问题解决
1. 路径问题
    - 使用绝对路径变量：${PROJECT_SOURCE_DIR}（源码根目录）和${PROJECT_BINARY_DIR}（构建目录）。
2. 库链接失败
    - 指定库搜索路径：
        ```cmake
        link_directories(/usr/local/lib)  # 全局库目录
        ```
3. 跨平台兼容性
    - 使用configure_file()生成平台适配的头文件。
---
### 六、完整示例
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyApp VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
file(GLOB SOURCES "src/*.cpp")
add_executable(MyApp ${SOURCES})
target_include_directories(MyApp PRIVATE include)
find_package(OpenCV REQUIRED)
target_link_libraries(MyApp PRIVATE ${OpenCV_LIBS})
install(TARGETS MyApp DESTINATION bin)
```
---
通过以上方法，可覆盖从简单项目到复杂工程的需求。实际开发中建议结合官方文档（cmake --help-command查看命令详情）灵活调整。