# Student Manager

一个基于 C++ 控制台的学生信息管理系统，采用单向链表存储数据，支持增删改查、排序、文件保存与加载，并通过 SHA-256 密码验证保护数据安全。

## 功能

- 密码登录 – 使用 SHA-256 验证，防止未授权访问
- 添加学生 – 录入学号、姓名，自动分配唯一 ID
- 删除学生 – 根据 ID 删除，尾指针 O(1) 更新
- 修改学生 – 更新学号和姓名
- 查找学生 – 按 ID 快速查找并显示信息
- 显示全部 – 列表式展示所有学生
- 统计人数 – 显示当前学生总数
- 排序 – 按学号升序排序（链表选择排序）
- 保存 / 加载 – 数据持久化为 CSV 文件，支持断点续用
- 输入校验 – 非法输入自动拦截，避免程序异常

## 默认密码

程序启动时需要输入密码 `lhm`。

> 密码通过 SHA-256 加密存储，不可直接查看明文。如需修改，请重新计算哈希并替换 `verify()` 中的 `correctHash` 常量。

## 文件结构

```
StudentManager/
├── StudentManager.cpp    # 主程序源码
├── students.csv          # 学生数据文件（自动生成）
└── README.md
```

## 编译与运行

### 依赖

- Windows 操作系统
- Microsoft Visual C++ 编译器（MSVC）或 MinGW-w64
- 库：`advapi32.lib`（已通过 `#pragma` 链接）

### 编译命令

```bash
g++ -std=c++11 -O2 -DNDEBUG -s -static -ffunction-sections -fdata-sections -Wl,--gc-sections StudentManager.cpp -o StudentManager.exe
```

### 运行

双击 `StudentManager.exe`，或在命令行中：

```bash
StudentManager.exe
```

## 使用说明

1. 启动程序后输入密码 `lhm`（输入时无回显，按 * 显示）。
2. 主菜单显示选项，按对应数字键操作：
   - `1` 添加学生
   - `2` 删除学生
   - `3` 查找学生
   - `4` 显示全部
   - `5` 修改信息
   - `6` 查看总人数
   - `7` 按学号排序
   - `8` 保存到文件
   - `9` 从文件加载
   - `0` 退出
3. 数据自动保存至 `students.csv`，下次启动可通过 `9` 加载。

## 注意事项

- 姓名不能包含逗号，否则 CSV 格式可能错乱。
- 学号目前仅支持整数输入。
- 程序运行于 Windows 控制台，依赖 `conio.h` 和 `windows.h`。

## 许可

仅用于学习目的，可自由修改和分发。

---

> Enjoy your student management!
