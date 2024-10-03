#include <iostream>
#include <conio.h>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <direct.h>
#include <windows.h>
#include <thread>
#include <chrono>

using namespace std;

string Hit_PASSWD="597486",User_PASSWD="123456",USR;

void SetConsoleColor(int color){
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,color);
}
inline void pwd(){
	char cwd[PATH_MAX];
	if(getcwd(cwd,sizeof(cwd))!=nullptr) cout<<cwd;
	else cerr<<"Error!";
}
inline void text_ui(string output,int mode){
	const string err_str="          #### ! ! ! ! !  E r r o r  ! ! ! ! ! ####";
	const string war_str="          ##### ! ! ! ! W a r n i n g ! ! ! ! #####";
	const string not_str="          ############## ! N o t e ! ##############";
	system("cls");
	string str;
	if(mode==0)system("color C0");
	if(mode==1)system("color EC");
	if(mode==2)system("color 9E");
	if(mode==0)str=err_str;
	if(mode==1)str=war_str;
	if(mode==2)str=not_str;
	cout<<endl<<endl<<endl;
	cout<<str<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##  ";
	cout<<output;
	for(int i=4+output.length();i<=36;i++){
		cout<<" ";
	}
	cout<<"  ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##    Press any key to continue...     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          #########################################"<<endl;
	getch();
	system("color 07");
	system("cls");
}
inline bool cd_path(const char* path) {
    if(chdir(path) != 0) {
        return 1;
    }
    else return 0;
}
inline void loading(int t){
	for(long long i=0;i<=t;i++){
		if(i%4==0){
			cout<<".";
			cout<<"\b-";
		}
		else if(i%4==1)cout<<"\b\\";
		else if(i%4==2)cout<<"\b|";
		else if(i%4==3)cout<<"\b/";
		this_thread::sleep_for(chrono::milliseconds(200));
	}
}
inline string input_ui(string output){
	system("cls");
	COORD pos={14+output.length(),7};
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	cout<<endl<<endl<<endl;
	cout<<"          ################# Input #################"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##  ";
	cout<<output;
	for(int i=4+output.length();i<=36;i++){
		cout<<"_";
	}
	cout<<"  ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          #########################################"<<endl;
	SetConsoleCursorPosition(hOut,pos);
	string str;
	cin>>str;
	SetConsoleCursorPosition(hOut,pos);
	for(int i=4+output.length();i<=36;i++){
		cout<<"_";
	}
	cout<<endl<<endl<<endl<<endl<<endl;
	system("cls");
	return str;
}
inline string input_ui_passwd(string output){
	system("cls");
	COORD pos={14+output.length(),7};
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	cout<<endl<<endl<<endl;
	cout<<"          ################# Input #################"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##  ";
	cout<<output;
	for(int i=4+output.length();i<=36;i++){
		cout<<"_";
	}
	cout<<"  ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          ##                                     ##"<<endl;
	cout<<"          #########################################"<<endl;
	SetConsoleCursorPosition(hOut,pos);
	string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        } else {
            password.push_back(ch);
            std::cout << '*';
        }
    }
	SetConsoleCursorPosition(hOut,pos);
	for(int i=4+output.length();i<=36;i++){
		cout<<"_";
	}
	cout<<endl<<endl<<endl<<endl<<endl;
	system("cls");
	return password;
}
inline void p(){
	cout<<"\n"<<USR<<" [";
	pwd();
	cout<<"] >>>";
}
inline void start(){
	for(int i=1;i<=100;i++) {
		cout<<"loading..."<<i<<"%\n";
		system("cls");
	}
	cout<<"Please wait...\n";
	loading(10);
	cout<<"\nHitmux 1.0-stable (C) 2024 CaoKai,All right reserved.\n";
	cout<<"Hitmux 1.0-stable (C) 2024 CaoKai,All right reserved.\n";
	cout<<"Hitmux 1.0-stable (C) 2024 CaoKai,All right reserved.\n\n";
	cout<<"#    #\n";
	cout<<"#    #  #    #\n";
	cout<<"######     ##### ##### #  # #   #\n";
	cout<<"#    #  #    #   # # # #  #   #\n";
	cout<<"#    #  #    ##  # # # #### #   #\n";
	cout<<"Author:CaoKai in Nazi Germany.\nEmail:caokai674@gmail.com\n";
	Sleep(1);
	cout<<"\n\n";
}
inline void shutdown(){
	cout<<"I will shutdown your Hitmux system.";
	cout<<"Please wait...\n";
	loading(6);
	cout<<"\nRemove temp data...\n";
	cout<<"Shutdown system...\n";
	Sleep(1);
}
inline void init(){
	bool de_1=1;
	while(1){
		if(de_1)cout<<"Hitmux 1.0-stable (C) 2024 CaoKai,All right reserved.\n";
		cout<<"1.Hit mode.\n"<<"2.User mode.\n"<<"3.Visitor mode\n";
		string de_start="\0";
		cin>>de_start;
		string passwd="\0";
		if(de_start=="1"){
		passwd=input_ui_passwd("Password of Hit:");
			if(passwd==Hit_PASSWD){
				USR="Hit";
				text_ui("Best no spaces in the path",2);
				getchar();
				break;
			}
			else{
				de_1=0;
				text_ui("Password error!",0);
				getchar();
			}
		}
		else if(de_start=="2"){
			passwd=input_ui_passwd("Password of User:");
			if(passwd==User_PASSWD){
				USR="User";
				text_ui("Best no spaces in the path",2);
				start();
				getchar();
				break;
			}
			else{
				de_1=0;
				text_ui("Password error!",0);
				getchar();
			}
		}
		else if(de_start=="3"){
			USR="Visitor";
			text_ui("Best no spaces in the path",2);
			start();
			getchar();
			break;
		}
		else {
			text_ui("Must input \"1\",\"2\" or \"3\"",0);
			getchar();
		}
	}
	cout<<"If you are not familiar with the Hitmux system, you can use the \"allcmd\" command\nOr contact the author's email address";
}

int main(){
	init();
	while(true){
		string input;
		p();
	    getline(cin, input);
		string a[64];
		fill_n(a,64,"\0");
	    int co=0;
	    istringstream iss(input);
	    while (iss>>a[co]){
	    	co++;
	    }
	    
	    if(a[0]=="pwd"){
	    	pwd();
		}
		else if(a[0]=="upg"&&USR=="Hit"){
			text_ui("There may be some issues!",2);
			cout<<"I may delete some of your temp dataand take up more disk hard space to updata your system\nAre you sure?(N/Y)";
			string de_up;
			cin>>de_up;
			if((de_up=="Y")||(de_up=="y")){
				cout<<"This system name must be\"Hitmux.exe\"(Windows) or \"Hitmux\"(Linux)\n";
				cout<<"Please input the updata program path:";
				string path;
				getline(cin,path);
				getchar();
				shutdown();
				const char *temp_upgrade=path.c_str();
				system(temp_upgrade);
			}
			else cout<<"Cancel";
		}
		else if(a[0]=="upg"&&USR!="Hit"){
			cout<<"Permission Denied.";
		}
		else if(a[0]=="cd"){
			const char *ch=a[1].c_str();
			if(a[1]!="\0"&&access(ch,F_OK)!=-1) cd_path(ch);
			else if(a[1]=="\0") cout<<"Error!";
			else if(access(ch,F_OK)==-1) cout<<"No such directory.";
		}
		else if(a[0]=="time"){
			time_t t=time(nullptr);
			tm*now=localtime(&t);
			cout<<put_time(now,"%Y-%m-%d %H:%M:%S")<<endl;
		}
		else if(a[0]=="mv"){
			cout<<"Please wait sometime,CaoKai will add this command: "<<a[0]<<".";
		}
		else if(a[0]=="rm"){
		    if(USR!="Hit"&&USR!="User") cout<<"Permission denied.";
			else if(a[1]=="-s"&&a[2]!="\0"){
				const char *temp_rm=a[1].c_str();
				int re_rm=remove(temp_rm);
				if(re_rm==0) cout<<"Succeed!";
				else cout<<"Can't remove this file!";
			}
			else if(a[1]=="-r"&&a[2]!="\0"){
				const char *temp_rm1=a[2].c_str();
				int re_rm1=rmdir(temp_rm1);
				if(re_rm1==0) cout<<"Succeed!";
				else cout<<"Can't remove this folder!";
			}
			else cout<<"Error!";
		}
		else if(a[0]=="mkd"){
			if(a[1]!="\0"){
				const char *temp_mkd=a[1].c_str();
				int re_mkd=mkdir(temp_mkd);
				if(re_mkd==0) cout<<"Succeed!";
				else cout<<"Cannot create this folder!";
			}
			else cout<<"Error!";
		}
		else if(a[0]=="ls"){
			cout<<system("dir");
		}
		else if(a[0]=="mkf"){
		    if(a[1]!="\0"){
		        string temp_mkf="type nul > "+a[1];
		        const char *temp_mkf_1=temp_mkf.c_str();
		        system(temp_mkf_1);
		    }
		    else cout<<"Error!";
		}
		else if(a[0]=="sd"){
			text_ui("You will lost all of the data!",1);
			shutdown();
			return 0;
		}
		else if(a[0]=="pswd"){
			if(a[1]=="Hit"&&a[2]!="\0"&&USR=="Hit") Hit_PASSWD=a[2];
			else if(USR=="Visitor") cout<<"Permission denied.";
			else if(a[1]=="User"&&a[2]!="\0"&&(USR=="Hit"||USR=="User")){
				User_PASSWD=a[2];
				cout<<"Succeed!";
			}
			else if(a[1]=="\0") cout<<"No user entered!";
			else if(a[2]=="\0") cout<<"No new password entered!";
			else if(a[1]!="User"&&a[1]!="Hit") cout<<"There is no such user or the user cannot change the password！";
			else cout<<"Error!";
			
		}
		else if(a[0]=="su"){
			if(a[1]!="\0"){
				if(a[1]=="User") {
					cout<<"Enter password:";
					string temp_pswd_su;
					cin>>temp_pswd_su;
					getchar();
					if(temp_pswd_su==User_PASSWD) USR="User";
				}
				else if(a[1]=="Hit"){
					cout<<"Enter password:";
					string temp_pswd_su1;
					cin>>temp_pswd_su1;
					getchar();
					if(temp_pswd_su1==Hit_PASSWD) USR="Hit";
				}
				else if(a[1]=="Visitor") USR="Visitor";
			}
		}
		else if(a[0]=="cle"){
			system("cls");
		}
		else if(a[0]=="allcmd"){
			cout<<"*************\n";
			cout<<"<>is required item,[]is Optional options and {}isExplanation of a certain item.\n\n";
			cout<<"<cd> <path>\nSwitch working path.\n\n";
			cout<<"<ls>\nList all files and folders in the current directory.\n\n";
			cout<<"<rm> <option> <path>\nRemove file{s} or folder{s}\noption:\n    -r:Recursive deletion of folders and all files inside.\n    -s:Remove a file.\n\n";
			cout<<"<mv> <path1> <path2>\nMove path1 to path2.\n\n";
			cout<<"<time>\nOutput current time.\n\n";
			cout<<"<pwd>\nList the current working directory.\n\n";
			cout<<"<pswd> <user> <new password>/nChange the password of a system level user.\n\n";
			cout<<"<su> <user>\n<password>{Except Visitor or non system level users.\n}Change a user's password.\n\n";
			cout<<"<upg>\n...\nUpdate the system.\n\n";
			cout<<"<cle>\nClear the screen.\n\n";
			cout<<"<mkd> <path>\nMake a new directory.\n\n";
			cout<<"<allcmd>\nList the usage of all commands.\n\n";
			cout<<"<mkf> <path>\nMake a new empty file.\n\n";

			cout<<"<help> <command>\nView the usage of a command.\n\n";
			cout<<"*************";
		}
		else if(a[0]=="help"){
			if(a[1]=="cd") cout<<"<cd> <path>\nSwitch working path.";
			else if(a[1]=="ls") cout<<"<ls>\nList all files and folders in the current directory.";
			else if(a[1]=="rm") cout<<"<rm> <option> <path>\nRemove file{s} or folder{s}\noption:\n    -r:Recursive deletion of folders and all files inside.\n    -s:Remove a file.";
			else if(a[1]=="mv") cout<<"<mv> <path1> <path2>\nMove path1 to path2.";
			else if(a[1]=="time") cout<<"<time>\nOutput current time.";
			else if(a[1]=="pwd") cout<<"<pwd>\nList the current working directory.";
			else if(a[1]=="pswd") cout<<"<pswd> <user> <new password>/nChange the password of a system level user.";
			else if(a[1]=="su") cout<<"<su> <user>\n<password>{Except Visitor or non system level users.}\nChange a user's password.";
			else if(a[1]=="upg") cout<<"<upg>\n...\nUpdate the system.";
			else if(a[1]=="cle") cout<<"<cle>\nClear the screen.";
			else if(a[1]=="mkd") cout<<"<mkd> <path>\nMake a new directory.";
            		else if(a[1]=="mkf") cout<<"<mkf> <path>\nMake a new empty file.";
			else if(a[1]=="allcmd") cout<<"<allcmd>\nList the usage of all commands.";
			else cout<<"<help> <command>\nView the usage of a command.\n<>is required item,[]is Optional options and {}isExplanation of a certain item./n";
		}
		else cout<<"\nCommand not found.";
	}
	return 0;
}
