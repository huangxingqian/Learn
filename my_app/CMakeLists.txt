cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(my_app VERSION 1.0 LANGUAGES C)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 头文件路径
include_directories(include)

# 源文件
set(SOURCES
    src/main.c
    src/utils.c
)

# 生成可执行文件
add_executable(my_app ${SOURCES})

# 设置输出路径
set_target_properties(my_app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# 安装规则（可选）
install(TARGETS my_app DESTINATION bin)
