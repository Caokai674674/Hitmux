# Hitsw-1.0-Standard

[English](https://github.com/CaoKai674/Hitmux/Hitsw/hitsw-1.0-standard-en.md)

自从 Hitmux-3.0.0-beta 版本开始，Hitmux 支持了第三方插件（以下简称 sw ）。

这是给开发者提供的开发标准，只有遵循该标准的 sw 才可以在 Hitmux 中使用。

---

### 一、插件定义及命名

---
1. 定义：任何符合 Hitsw 标准并可以在 Hitmux 中跨平台使用的插件都可以称为 sw。我们鼓励开源。
2. 主命令：任何一个 sw 都要有主命令，主命令是在 Hitmux-shell 中执行 sw 所使用的命令。
3. 命名：sw 的源代码命名规则为：Hitsw-主命令-版本号。
4. 可执行文件：sw的二进制文件命名规则为：lib主命令.dll（Windows）或 lib主命令.so（Linux）。

---

### 二、插件目录
#### sw 的目录有以下几种：

---
1. 插件二进制文件目录
2. 动态链接库文件目录
3. 插件配置文件目录
4. 其他数据文件目录

---

* 这些目录在 Hitmux 安装 sw 时自动创建。

* 如何获取这些目录？见 “三、插件开发 3.环境变量”。

### 三、插件开发

1. 建议使用 C++ 语言。我们只提供 C++ 语言的开发模板，其他语言的开发者可以自行转换。
2. 需遵照的框架：

```cpp

#include "plugin.h" //需要包含 plugin.h 头文件

/*

"any type" f1(vector<string> args) {
    //api函数     
}

......
你的程序

*/

//必须包含一下代码：
extern "C" {
    FunctionMap* register_functions() {
        FunctionMap* funcs = new FunctionMap();
        (*funcs)["command"] = f1; //f1是 api 函数名，command 是主命令名。
        return funcs;
    }
}

```
其中，"plugin.h" 在 Hitmux 的源代码文件中，位于 Hitsw/plugin.h 。

其中，```(*funcs)["command"] = f1;``` 代码中，"command" 是主命令名，"f1" 是 api 函数名。command 必须符合 C++ 命名规范，并且在 同一个 Hitmux 系统中唯一，否则可能运行时会导致问题。

api 函数的返回值类型任意，接受的参数：vector<string> args。args 是一个字符串数组，包含了命令行参数。

我们还提供了一个 Hello World 示例，位于 Hitsw/HelloWorld.cpp 。

3. 环境变量
在头文件 plugin.h 中，我们提供了一个函数：std::string H_get_evn(int num)，用来获取 Hitmux 的环境变量。

该函数返回的字符串包含了以下信息：（注意：下标从 0 开始！）

---
- 0. sw 的安装目录。
- 1. sw 的二进制文件目录。
- 2. sw 的动态链接库目录。
- 3. sw 的配置文件目录。    
- 4. sw 的数据文件目录。
- 5. Hitmux 的版本号。

---

例如：通过 H_get_evn() 函数，你可以获取到 sw 的安装目录：

```cpp
#include "plugin.h"

int main() {
    std::string env = H_get_evn(0);
    cout << "Hitmux home: " << env << endl;
    return 0;
}
```


### 四、二进制文件编译
1. G++ 编译：

```bash
g++ -shared -fPIC -o lib主命令.so(dll) 你的源代码.cpp
```

我们建议使用 g++ 编译器并开启 -O2 优化选项。

2. 编译后的文件命名规则为：lib主命令.so (Linux) 或 lib主命令.dll (Windows)，然后将其放入 Hitmux 的 plugins 目录下（见 “二、插件目录结构”）。
3. 如果你已经运行了 Hitmux，可以考虑使用 Hitmux-shell 中的 sw build 命令来编译 sw。其中,sw build 命令语法：

```bash
sw build 主命令  编译器参数1 编译器参数2...
```
其中，编译器参数省缺值为：-shared -fPIC -O2。

例如：
```bash
sw build example
```
就会使用 g++ -shared -fPIC -O2 -o libexample.so(dll) example.cpp 编译 ./example.cpp 。

### 五、插件安装与卸载
1. 安装：
你可以在 Hitmux-shell 中执行 sw install 命令来把 sw 安装到 Hitmux 中。sw install 命令会自动建立 sw 的其他文件。其中，sw install 命令语法：
```bash
sw install 主命令
```
例如：
```bash
sw install example
```

2. 卸载 sw：
可以使用 sw uninstall 命令来卸载 sw。其中，sw uninstall 命令语法：
```bash
sw uninstall 主命令 
```

3. 注意：
- 不建议自行编译/删除/安装 sw，建议使用 sw build、sw install 和 sw uninstall 命令。
- 不建议随意修改 sw 的配置文件和动态链接库文件，否则可能导致运行时出现问题。


---

联系我们：<hitmux674@gmail.com>