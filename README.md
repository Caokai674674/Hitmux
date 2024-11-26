Caokai-Hitmux
=============
* Hitmux is a command-line software that I developed during my free time. 
It currently has versions for both Linux and Windows.
The software is written in C++. 
If you have any questions, you can contact me at caokai674@gmail.com.
The default password for Hit mode is NULL, and the default password for User mode is NULL.

* Hitmux 是我在空闲时间开发的一个命令行软件。 
目前它有适用于 Linux 和 Windows 的版本。
该软件是用C++编写的。 
如果您有任何疑问，可以通过caokai674@gmail.com与我联系。
Hit 模式的默认密码为 NULL，User 模式的默认密码为 NULL。

2.1.0-beta major update!
2.1.0-beta 重磅更新！
-----------
Hitmux 2.1.0-beta (C) 2024 CaoKai,All right reserved.
* 1.Add a security module to prevent password cracking. 添加安全模块，防止密码破解。
* 2.Add "cp" command, which can copy files. 添加“cp”命令，可以复制文件。
* 3.Add the code for the "mv" command, now the "mv" command can be used. 添加“mv”命令的代码，现在“mv”命令可以使用了。
* 4.Add "clock" command to display graphical clock. 添加“clock”命令，可以显示图形化的时钟。
* 5.Optimize "su" command and "pswd" command. 优化“su”命令和“pswd”命令。
* 6.Optimize data storage logic and be more friendly to hard disks. 优化数据储存逻辑，对硬盘更友好。
* 7.Merge the "CLOG.h" header file into "HELP.h". 把“CLOG.h”头文件合并进“HELP.h”。

Compile and run:
编译与运行：
-----------
Versions 2.1.0-beta and above need to install the EGE library. 2.1.0-beta及以上版本需要安装EGE库。
Download 下载：https://xege.org/

* Command on Windows:
* Windows上的命令：
```bash
g++ -o Hitmux.exe ***.cpp -O2
//2.1.0-beta and above: 2.1.0-beta及以上版本：
g++ -o Hitmux.exe ***.cpp -O2 -lgraphics -lgdi32 -lgdiplus
Hitmux.exe
```

Forgot your password?
忘记了密码？
-----------
* Download 下载[Password-reset.exe](https://github.com/Caokai674674/Hitmux/tree/main/Password-reset)
