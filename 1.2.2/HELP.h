#ifndef HELP_H
#define HELP_H

#include <iostream>
#include <string>
using namespace std;

inline void allcmd_f(){
	cout<<"********\n";
	cout<<"cd\n";
	cout<<"ls\n";
	cout<<"rm\n";
	cout<<"mv\n";
	cout<<"time\n";
	cout<<"pwd\n";
	cout<<"pswd\n";
	cout<<"su\n";
	cout<<"upg\n";
	cout<<"cle\n";
	cout<<"mkd\n";
	cout<<"allcmd\n";
	cout<<"mkf\n";
	cout<<"help\n";
	cout<<"cal\n";
	cout<<"clog\n";
	cout<<"gmh\n";
	cout<<"********\n";
	cout<<"Use the \"help\" command to see specific usage.\n";
	cout<<"********";
}
inline void help_f(string a){
	cout<<"******************************\n<>is required item,[]is Optional options and {}isExplanation of a certain item.\n\n";
	if(a=="cd") cout<<"cd <path>\nSwitch working path.";
	else if(a=="ls") cout<<"ls\nList all files and folders in the current directory.";
	else if(a=="rm") cout<<"rm <option> <path>\nRemove file{s} or folder{s}\noption:\n    -r:Recursive deletion of folders and all files inside.\n    -s:Remove a file.";
	else if(a=="mv") cout<<"mv <path1> <path2>\nMove path1 to path2.";
	else if(a=="time") cout<<"time\nOutput current time.";
	else if(a=="pwd") cout<<"pwd\nList the current working directory.";
	else if(a=="pswd") cout<<"pswd <user> <new password>/nChange the password of a system level user.";
	else if(a=="su") cout<<"su <user>\n<password>{Except Visitor or non system level users.}\nChange a user's password.";
	else if(a=="upg") cout<<"upg\n...\nUpdate the system.";
	else if(a=="cle") cout<<"cle\nClear the screen.";
	else if(a=="mkd") cout<<"mkd <path>\nMake a new directory.";
    else if(a=="mkf") cout<<"mkf <path>\nMake a new empty file.";
	else if(a=="allcmd") cout<<"allcmd\nList the usage of all commands.";
	else if(a=="clog") cout<<"clog\nView changelog.";
	else if(a=="cal") cout<<"cal <first number> <operator> [second number]\nPowerful NB calculator (C) 2024 CaoKai,All right reserved.\nA powerful veryNB calculator.\noperator:\n    +:Addition.\n    -:Subtraction.\n    *:Multiplication.\n    /:Division\n    ^:Power\n    -log:Logarithm.\n    -tan:Tangent.\n    -sin:Sine.\n    -cos:Cosine.\n{If you want to calculate trigonometric functions (sin, cos, tan), you only need to enter the first number!}";
	else if(a=="gmh") cout<<"gmh Launch game menu";
	else cout<<"<help> <command>\nView the usage of a command.\n<>is required item,[]is Optional options and {}isExplanation of a certain item./n";
	}
#endif
