# Pytest 使用方法指南

Pytest 是 Python 中最流行的测试框架之一，它简单易用但功能强大。以下是 Pytest 的主要使用方法：

## 安装 Pytest

```bash
pip install pytest
```

## 基本使用

1. **创建测试文件**：测试文件应以 `test_` 开头或 `_test.py` 结尾
2. **编写测试函数**：测试函数应以 `test_` 开头

```python
# test_sample.py
def func(x):
    return x + 1

def test_answer():
    assert func(3) == 5  # 这个测试会失败
```

3. **运行测试**：

```bash
pytest
```

## 常用断言

Pytest 使用 Python 的 `assert` 语句进行断言：

```python
def test_assertions():
    assert 1 == 1
    assert "hello" in "hello world"
    assert [1, 2] == [1, 2]
    with pytest.raises(ValueError):
        raise ValueError
```

## Fixture（夹具）

Fixture 是 Pytest 的核心功能之一，用于提供测试所需的固定环境：

```python
import pytest

@pytest.fixture
def sample_data():
    return [1, 2, 3, 4, 5]

def test_sum(sample_data):
    assert sum(sample_data) == 15
```

## 参数化测试

使用 `@pytest.mark.parametrize` 可以轻松实现参数化测试：

```python
import pytest

@pytest.mark.parametrize("input,expected", [
    (3, 4),
    (5, 6),
    (10, 11),
])
def test_func(input, expected):
    assert func(input) == expected
```

## 常用命令行选项

- `pytest -v`: 详细输出
- `pytest -k "expression"`: 运行名称匹配表达式的测试
- `pytest -m mark`: 运行标记的测试
- `pytest --collect-only`: 只收集测试不运行
- `pytest --lf`: 只运行上次失败的测试
- `pytest -x`: 遇到第一个失败后停止
- `pytest --pdb`: 测试失败时进入调试模式

## 测试标记

可以为测试添加标记：

```python
@pytest.mark.slow
def test_slow_function():
    import time
    time.sleep(10)
    assert True
```

然后可以这样运行标记的测试：

```bash
pytest -m slow
```

## 测试覆盖率

安装 coverage 插件：

```bash
pip install pytest-cov
```

运行测试并检查覆盖率：

```bash
pytest --cov=myproject tests/
```

## 测试目录结构

典型的测试目录结构：

```
project/
│
├── mypackage/
│   ├── __init__.py
│   └── module.py
│
└── tests/
    ├── __init__.py
    ├── test_module.py
    └── integration/
        └── test_integration.py
```

## 高级特性

1. **临时目录**：使用 `tmpdir` fixture
2. **猴子补丁**：使用 `monkeypatch` fixture
3. **捕获输出**：使用 `capsys` fixture
4. **测试异常**：使用 `pytest.raises`
5. **跳过测试**：使用 `@pytest.mark.skip` 或 `@pytest.mark.skipif`

Pytest 功能非常丰富，以上只是基础使用方法。随着项目复杂度增加，可以探索更多高级特性如插件系统、钩子函数等。