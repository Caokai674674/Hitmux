# Hitsw-1.0-Standard

[简体中文](https://github.com/Caokai674674/Hitmux/blob/main/Hitsw/hitsw-1.0-standard-zh.md)

Since Hitmux-3.0.0-beta, Hitmux supports third-party plugins (referred to as sw hereafter).

This is a development standard for developers. Only sw that follows this standard can be used in Hitmux.

---

### 1. Plugin Definition and Naming

---

1. **Definition**: Any plugin that complies with the Hitsw standard and can be used cross-platform within Hitmux is called sw. We encourage open-source contributions.
2. **Main Command**: Every sw must have a main command, which is the command used to execute the sw in the Hitmux-shell.
3. **Naming**: The source code of sw should follow this naming rule: Hitsw-main_command-version_number.
4. **Executable File**: The naming rule for sw’s binary file is: libmain_command.dll (Windows) or libmain_command.so (Linux).

---

### 2. Plugin Directory

The directories for sw are as follows:

---

1. Plugin binary file directory
2. Dynamic link library directory
3. Plugin configuration file directory
4. Other data files directory

---

* These directories are automatically created when Hitmux installs a sw.

* To retrieve these directories, refer to “3. Plugin Development 3. Environment Variables.”

### 3. Plugin Development

1. It is recommended to use C++ for development. We only provide a C++ development template; developers using other languages can convert it themselves.
2. Required framework:

```cpp
#include "plugin.h" // Include the plugin.h header file

/*
"any type" f1(vector<string> args) {
    // API function
}

......

Your program

*/

// Must include the following code:
extern "C" {
    FunctionMap* register_functions() {
        FunctionMap* funcs = new FunctionMap();
        (*funcs)["command"] = f1; // f1 is the API function, command is the main command.
        return funcs;
    }
}
```

In this code, `"plugin.h"` is located in the Hitmux source code files under `Hitsw/plugin.h`.

Here, `(*funcs)["command"] = f1;` means `"command"` is the main command, and `f1` is the API function. The command must adhere to C++ naming conventions and be unique within the same Hitmux system, as duplicate commands may lead to runtime issues.

The API function can return any type and accepts a `vector<string> args` parameter, where `args` is a string array containing the command-line arguments.

We also provide a Hello World example in `Hitsw/HelloWorld.cpp`.

3. **Environment Variables**  
In the `plugin.h` file, we provide a function `std::string H_get_evn(int num)` to retrieve Hitmux’s environment variables.

The returned string contains the following information (indices start from 0!):

---
- 0. sw installation directory.
- 1. sw binary file directory.
- 2. sw dynamic library directory.
- 3. sw configuration file directory.    
- 4. sw data file directory.
- 5. Hitmux version number.

---

For example, you can use `H_get_evn()` to get the sw installation directory:

```cpp
#include "plugin.h"

int main() {
    std::string env = H_get_evn(0);
    cout << "Hitmux home: " << env << endl;
    return 0;
}
```

### 4. Compiling Binary Files

1. **G++ Compilation**:

```bash
g++ -shared -fPIC -o libmain_command.so (or .dll) your_source_code.cpp
```

We recommend using the g++ compiler with the `-O2` optimization option.

2. The compiled file should be named `libmain_command.so` (Linux) or `libmain_command.dll` (Windows) and placed into the Hitmux `plugins` directory (see “2. Plugin Directory Structure”).

3. If you have already run Hitmux, you can use the `sw build` command in Hitmux-shell to compile the sw. The syntax for the `sw build` command is:

```bash
sw build main_command compiler_argument1 compiler_argument2...
```

The default compiler arguments are `-shared -fPIC -O2`.

For example:

```bash
sw build example
```

This will use `g++ -shared -fPIC -O2 -o libexample.so (or .dll) example.cpp` to compile `./example.cpp`.

### 5. Plugin Installation and Uninstallation

1. **Installation**:  
You can install sw into Hitmux using the `sw install` command. The `sw install` command will automatically set up the sw’s other files. The syntax for the `sw install` command is:

```bash
sw install main_command
```

For example:

```bash
sw install example
```

2. **Uninstallation**:  
You can uninstall sw using the `sw uninstall` command. The syntax for the `sw uninstall` command is:

```bash
sw uninstall main_command
```

3. **Note**:
- It is not recommended to manually compile/delete/install sw. It is better to use the `sw build`, `sw install`, and `sw uninstall` commands.
- Avoid modifying sw’s configuration files and dynamic libraries, as this could cause runtime issues.

---

**Contact Us**: <hitmux674@gmail.com>

---
