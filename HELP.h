#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <string>
using namespace std;

inline void clog_h(){
	cout<<"*****************************************************\n\n";
	
	cout<<"Hitmux 1.0-stable (C) 2024 CaoKai,All right reserved.\n";
	cout<<"Hitmux is a command-line software that I developed during my free time.\n";
	cout<<"It currently has versions for both Linux and Windows. The software is written in C++.\n";
	cout<<"If you have any questions, you can contact me at caokai674@gmail.com.\n";
	cout<<"*****************************************************\n\n";
	
	cout<<"Hitmux 1.1.0-stable (C) 2024 CaoKai,All right reserved.\n";
	cout<<"The author lost the source code.\n";
	cout<<"*****************************************************\n\n";
	
	cout<<"Hitmux 1.2.0-beta (C) 2024 CaoKai,All right reserved.\n";
	cout<<"1. Put a large number of functions into header files to reduce development difficulty.\n";
	cout<<"2. Added \"clog\" command.\n";
	cout<<"3. Fix some problems of \"cla\" calculator.\n";
	cout<<"4. Modify some UI.\n";
	cout<<"*****************************************************\n\n";
	
	cout<<"Hitmux 1.2.1-beta (C) 2024 CaoKai,All right reserved.\n";
	cout<<"1. Add game functions and use the command \"gmh\" to start.\n";
	cout<<"2. Improve prompts, warnings, and error Us.\n";
	cout<<"3. Fix some bugs.\n";
	cout<<"*****************************************************\n\n";
	
	cout<<"Hitmux 1.2.2 (C) 2024 CaoKai,All right reserved.\n";
	cout<<"1. Add x86 emulator\n";
	cout<<"2. Fix startup bug\n";
	cout<<"3. Fix some bugs.\n";
	cout<<"*****************************************************\n";
	
	cout<<"Hitmux 2.0.0-very_unstable (C) 2024 CaoKai,All right reserved.\n";
	cout<<"1.Can retain operating system data instead of losing all data every time it is shut down.\n";
	cout<<"2.Add header file \"SYSTEM.h\".\n";
	cout<<"3.This version is very unstable, and sometimes it even fails to start properly!\n";
	cout<<"*****************************************************\n";

	printf("Hitmux 2.0.1-stable (C) 2024 CaoKai,All right reserved.\n");
	printf("1. Fix serious problems in version 2.0.0.\n");
	printf("2. Change the default password for User and Hit modes to \"NULL\".");
	printf("3. This version is stabler than 2.0.0.\n");
	printf("*****************************************************\n\n");

	printf("Hitmux 2.1.0-beta (C) 2024 CaoKai,All right reserved.\n");
	printf("1. Add a security module to prevent password cracking.\n");
	printf("2.Add \"cp\" command, which can copy files.\n");
	printf("3. Add the code for the \"mv\" command, now the \"mv\" command can be used.\n");
	printf("4. Add \"clock\" command to display graphical clock.\n");
	printf("5. Optimize \"su\" command and \"pswd\" command.\n");
	printf("6. Optimize data storage logic and be more friendly to hard disks.\n");
	printf("7. Merge the \"CLOG.h\" header file into \"HELP.h\".\n");
	printf("*****************************************************\n\n");
}

inline void allcmd_f(){
	cout<<"********\n";
	cout<<"cd\n";
	cout<<"ls\n";
	cout<<"rm\n";
	cout<<"cp **new\n";
	cout<<"mv **changed\n";
	cout<<"time\n";
	cout<<"pwd\n";
	cout<<"pswd **changed\n";
	cout<<"su **changed\n";
	cout<<"upg\n";
	cout<<"cle\n";
	cout<<"mkd\n";
	cout<<"allcmd\n";
	cout<<"mkf\n";
	cout<<"help\n";
	cout<<"cal\n";
	cout<<"clog\n";
	cout<<"gmh\n";
	cout<<"clock **new\n";
	cout<<"********\n";
	cout<<"Use the \"help\" command to see specific usage.\n";
	cout<<"********";
}
inline void help_f(string a){
	cout<<"******************************\n<>is required item,[]is Optional options and {}isExplanation of a certain item.\n\n";
	if(a=="cd") cout<<"cd <path>\nSwitch working path.";
	else if(a=="ls") cout<<"ls\nList all files and folders in the current directory.";
	else if(a=="rm") cout<<"rm <option> <path>\nRemove file{s} or folder{s}\noption:\n    -r:Recursive deletion of folders and all files inside.\n    -s:Remove a file.";
	else if(a=="mv") cout<<"mv <option> <path1> <path2>\nMove path1 to path2.\noption:\n    -r:Move the folders and all files inside.\n    -s:Move a file.";
	else if(a=="cp") cout<<"cp <option> <path1> <path2>\nCopy path1 to path2.\noption:\n    -r:Copy the folders and all files inside.\n    -s:Copy a file.";
	else if(a=="time") cout<<"time\nOutput current time.";
	else if(a=="pwd") cout<<"pwd\nList the current working directory.";
	else if(a=="pswd") cout<<"pswd <user>/nChange the password of a system level user.";
	else if(a=="su") cout<<"su <user>\n<password>{Except Visitor or non system level users.}\nChange a user's password.";
	else if(a=="upg") cout<<"upg\n...\nUpdate the system.";
	else if(a=="cle") cout<<"cle\nClear the screen.";
	else if(a=="mkd") cout<<"mkd <path>\nMake a new directory.";
    else if(a=="mkf") cout<<"mkf <path>\nMake a new empty file.";
	else if(a=="allcmd") cout<<"allcmd\nList the usage of all commands.";
	else if(a=="clog") cout<<"clog\nView changelog.";
	else if(a=="cal") cout<<"cal <first number> <operator> [second number]\nPowerful NB calculator (C) 2024 CaoKai,All right reserved.\nA powerful veryNB calculator.\noperator:\n    +:Addition.\n    -:Subtraction.\n    *:Multiplication.\n    /:Division\n    ^:Power\n    -log:Logarithm.\n    -tan:Tangent.\n    -sin:Sine.\n    -cos:Cosine.\n{If you want to calculate trigonometric functions (sin, cos, tan), you only need to enter the first number!}";
	else if(a=="gmh") cout<<"gmh Launch game menu";
	else if(a=="clock") printf("clock\nDisplays a graphical clock.");
	else cout<<"<help> <command>\nView the usage of a command.\n<>is required item,[]is Optional options and {}isExplanation of a certain item.";
	}
	
#endif
