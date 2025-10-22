# OpenGL 项目开发日志

## 2025/9/28 - 基础窗体与事件回调

### 主要功能
- **创建基础窗体**：初始化窗口系统（如使用 GLFW 或 SDL）。
- **事件回调函数**：
  - 在窗体激活状态下，响应以下用户交互事件：
    - 窗口大小变化
    - 键盘输入
    - 鼠标移动与点击

---

## 2025/9/29 - 添加 OpenGL 查错代码

### 功能说明
添加 OpenGL 错误检测机制，用于在运行时捕获并输出最近的 OpenGL 错误。

### 代码实现
```cpp
GLenum errorCode = glGetError(); // 检测和获取最近一次的 OpenGL 错误代码
std::string error = "";

if (errorCode != GL_NO_ERROR) { 
    switch (errorCode) {
        case GL_INVALID_ENUM:
            error = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "GL_INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            error = "GL_OUT_OF_MEMORY"; 
            break;
        default:
            error = "unknown error";
            break;
    }
    std::cout << error << std::endl;
}

---

## 2025/9/30 - 引入 Wrapper 层

### 结构调整
- 新增 `wrapper/` 文件夹，用于存放对第三方库的封装代码。
- 将 `checkError()` 函数从 `main.cpp` 移动至 `wrapper/` 目录下，实现代码解耦和复用。

---

## 2025/10/8 - 引入 `GL_CALL` 宏与预编译控制

### 新增功能
在 `checkError.h` 中添加宏定义 `GL_CALL(func)`，用于简化 `checkError()` 的调用。

### 预编译宏控制
使用 `DEBUG` 预编译宏控制错误检查的开启与关闭。

#### ❌ 初始错误实现（存在逻辑缺陷）
```cpp
#ifdef DEBUG
#define GL_CALL(func) func; checkError();
#else
#define GL_CALL(func) func;
#endif // DEBUG
```

#### ⚠️ 问题分析
该宏在控制流语句（如 `if-else`）中使用会导致**语法或逻辑错误**。

**示例问题代码**：
```cpp
if (someCondition)
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
else
    GL_CALL(glClearColor(1.0f, 0.0f, 0.0f, 1.0f));
```

**在 DEBUG 模式下展开后**：
```cpp
if (someCondition)
    glClear(GL_COLOR_BUFFER_BIT); checkError();
else
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); checkError();
```

**导致的问题**：
- `if` 语句只控制 `glClear(...);`
- `checkError();` 成为独立语句，不在 `if` 块内
- `else` 无法正确匹配，造成 **“dangling else”** 编译错误

---

### ✅ 正确实现：使用 `do { ... } while(0)`

#### 核心原理
C++ 语法中，`do { ... } while(0)` 将其内部的多条语句**封装为一条复合语句**，可安全用于控制流中。

#### 修正后的宏定义
```cpp
#ifdef DEBUG
#define GL_CALL(func) do { \
    func; \
    checkError(__FILE__, __LINE__); \
} while(0)
#else
#define GL_CALL(func) (func)
#endif
```

#### 使用示例
```cpp
if (condition)
    GL_CALL(glClear());
else
    GL_CALL(glClearColor());
```

#### 宏展开后（DEBUG 模式）
```cpp
if (condition)
    do {
        glClear();
        checkError(__FILE__, __LINE__);
    } while(0);
else
    do {
        glClearColor();
        checkError(__FILE__, __LINE__);
    } while(0);
```

✅ **结果**：
- `if` 控制的是整个 `do-while` 语句。
- `else` 正确匹配 `if`。
- 宏内部可包含任意多条语句，对外表现为**单条语句**，完全合法且安全。

> ✅ **结论**：`do { ... } while(0)` 是 C/C++ 宏定义中的经典技巧，用于确保多语句宏的安全使用。


#2025/10/22
添加application文件夹，封装单例类
```