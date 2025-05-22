# Google Test (gtest) 使用方法指南

Google Test（简称 gtest）是 Google 开发的 C++ 测试框架，用于编写单元测试。以下是 gtest 的基本使用方法：

## 1. 安装 gtest

### Linux 系统安装
```bash
sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
```

### 使用源码安装
1. 从 GitHub 下载源码：https://github.com/google/googletest
2. 编译安装：
```bash
mkdir build
cd build
cmake ..
make
sudo make install
```

## 2. 基本测试编写

### 测试文件结构
```cpp
#include <gtest/gtest.h>

// 测试用例1
TEST(TestSuiteName, TestName) {
    // 测试代码
    EXPECT_EQ(1, 1);  // 断言
}

// 测试用例2
TEST(TestSuiteName, AnotherTest) {
    // 测试代码
    ASSERT_TRUE(true);  // 断言
}

// 主函数
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

## 3. 常用断言

### 基本断言
- `EXPECT_EQ(val1, val2)`：验证 val1 == val2
- `EXPECT_NE(val1, val2)`：验证 val1 != val2
- `EXPECT_LT(val1, val2)`：验证 val1 < val2
- `EXPECT_LE(val1, val2)`：验证 val1 <= val2
- `EXPECT_GT(val1, val2)`：验证 val1 > val2
- `EXPECT_GE(val1, val2)`：验证 val1 >= val2

### 布尔断言
- `EXPECT_TRUE(condition)`：验证 condition 为 true
- `EXPECT_FALSE(condition)`：验证 condition 为 false

### 字符串断言
- `EXPECT_STREQ(str1, str2)`：验证两个 C 字符串相同
- `EXPECT_STRNE(str1, str2)`：验证两个 C 字符串不同

### ASSERT vs EXPECT
- `ASSERT_*`：失败时立即终止当前测试用例
- `EXPECT_*`：失败时继续执行当前测试用例

## 4. 测试夹具 (Test Fixtures)

```cpp
class MyFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // 每个测试用例开始前的初始化代码
    }
    
    void TearDown() override {
        // 每个测试用例结束后的清理代码
    }
    
    // 共享数据
    int sharedValue = 42;
};

TEST_F(MyFixture, Test1) {
    EXPECT_EQ(sharedValue, 42);
    sharedValue = 10;
}

TEST_F(MyFixture, Test2) {
    EXPECT_EQ(sharedValue, 42);  // 注意：每个测试用例都有独立的夹具实例
}
```

## 5. 参数化测试

```cpp
class ParamTest : public ::testing::TestWithParam<int> {
    // 可以使用 GetParam() 获取参数
};

TEST_P(ParamTest, EvenTest) {
    int n = GetParam();
    EXPECT_EQ(n % 2, 0);
}

INSTANTIATE_TEST_SUITE_P(EvenNumbers, ParamTest, ::testing::Values(2, 4, 6, 8));
```

## 6. 编译和运行

### CMake 配置示例
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyTests)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(
    my_tests
    test1.cpp
    test2.cpp
)

target_link_libraries(
    my_tests
    GTest::GTest
    GTest::Main
)

gtest_discover_tests(my_tests)
```

### 编译运行
```bash
mkdir build
cd build
cmake ..
make
./my_tests  # 运行所有测试
./my_tests --gtest_filter=TestSuiteName.TestName  # 运行特定测试
```

## 7. 常用命令行参数

- `--gtest_list_tests`：列出所有测试
- `--gtest_filter=POSITIVE_PATTERNS[-NEGATIVE_PATTERNS]`：过滤测试
- `--gtest_repeat=COUNT`：重复执行测试
- `--gtest_output=xml:FILE`：输出 XML 格式报告

## 8. 高级特性

- **类型参数化测试**：`TYPED_TEST` 和 `TYPED_TEST_P`
- **死亡测试**：`EXPECT_DEATH` 用于测试程序崩溃
- **事件监听器**：自定义测试输出
- **Mock 测试**：与 Google Mock 配合使用

通过以上方法，您可以有效地使用 gtest 来编写和组织 C++ 单元测试。