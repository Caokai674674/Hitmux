#include <iostream>
#include <conio.h>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <direct.h>
#include <windows.h>
#include <thread>
#include <chrono>
#include <cmath>

#include "UI.h"
#include "CAL.h"
#include "HELP.h"
#include "CLOG.h"
#include "X86.h"
#include "SYSTEM.h"

#include "GAME.h"//This header file include MINE-CLEARANCE.h and MINE_CLARANCE-2.1.3.h


using namespace std;
string system_data[8]={"NULL","NULL","NULL","NULL","NULL","NULL","NULL","NULL"},V_OF_H="2.0.0",YEAR="2024",USR;

inline void pwd(){
	char cwd[PATH_MAX];
	if(getcwd(cwd,sizeof(cwd))!=nullptr) cout<<cwd;
	else cerr<<"Error!";
}

inline bool cd_path(const char* path) {
    if(chdir(path) != 0) {
        return 1;
    }
    else return 0;
}

inline void p(){
	cout<<"] >>>";
}

inline void init(){
	r_init_f(system_data);
	w_init_f(system_data);
	fclose(stdout);
	freopen("CON","w",stdout);
	fflush(stdout);
	fclose(stdin);
	freopen("CON","r",stdin);
	fflush(stdin);
	setvbuf(stdout,NULL,_IONBF, 0);
	bool de_1=1;
	while(1){
		if(de_1)cout<<"Hitmux "<<V_OF_H<<" (C) "<<YEAR<<" CaoKai,All right reserved.\r\n";
		cout<<"1. Hit mode.\r\n2. User mode.\r\n3. Visitor mode.\r\n4. x86 Emulator\r\n";
		string de_start="\0";
		cin>>de_start;
		string passwd="\0";
		if(de_start=="1"){
		passwd=input_ui_passwd("Password of Hit:");
			if(passwd==system_data[0]){
				USR="Hit";
				text_ui("Don\'t enter spaces in the path!",2);
				getchar();
				cout<<"Hitmux "<<V_OF_H<<" (C) "<<YEAR<<" CaoKai,All right reserved.\r\n";
				cout<<"Hitmux "<<V_OF_H<<" (C) "<<YEAR<<" CaoKai,All right reserved.\r\n";
				cout<<"Hitmux "<<V_OF_H<<" (C) "<<YEAR<<" CaoKai,All right reserved.\r\n";
				cout<<"#    #\r\n";
				cout<<"#    #  #    #\r\n";
				cout<<"######     ##### ##### #  # #   #\r\n";
				cout<<"#    #  #    #   # # # #  #   #\r\n";
				cout<<"#    #  #    ##  # # # #### #   #"<<"  "<<V_OF_H<<"\r\n";
				cout<<"Author:CaoKai in Nazi Germany.\r\nEmail:caokai674@gmail.com\r\n";
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
			if(passwd==system_data[1]){
				USR="User";
				text_ui("Don\'t enter spaces in the path!",2);
				start(V_OF_H);
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
			start(V_OF_H);
			getchar();
			break;
		}
		else if(de_start=="4"){
			x86_f();
		}
		else{
			text_ui("Must input \"1\",\"2\",\"3\" or \"4\"",0);
			getchar();
		}
	}
	cout<<"If you are not familiar with the Hitmux system, you can use the \"allcmd\" command\r\nOr contact the author's email address";
}

int main(){
	init();
	while(true){
		w_init_f(system_data);
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
		else if(a[0]=="clog"){
			clog_h();
		}
		else if(a[0]=="upg"&&USR=="Hit"){
			text_ui("There may be some issues!",2);
			cout<<"I may delete some of your temp dataand take up more disk hard space to updata your system\r\nAre you sure?(N/Y)";
			string de_up;
			cin>>de_up;
			if((de_up=="Y")||(de_up=="y")){
				cout<<"This system name must be\"Hitmux.exe\"(Windows) or \"Hitmux\"(Linux)\r\n";
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
				const char *temp_rm=a[2].c_str();
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
			text_ui("Hitnux will be shut down!",1);
			shutdown();
			return 0;
		}
		else if(a[0]=="pswd"){
			if(a[1]=="Hit"&&a[2]!="\0"&&USR=="Hit") system_data[0]=a[2];
			else if(USR=="Visitor") cout<<"Permission denied.";
			else if(a[1]=="User"&&a[2]!="\0"&&(USR=="Hit"||USR=="User")){
				system_data[1]=a[2];
				cout<<"Succeed!";
			}
			else if(a[1]=="\0") cout<<"No user entered!";
			else if(a[2]=="\0") cout<<"No new password entered!";
			else if(a[1]!="User"&&a[1]!="Hit") cout<<"There is no such user or the user cannot change the password!";
			else cout<<"Error!";
			
		}
		else if(a[0]=="su"){
			if(a[1]!="\0"){
				if(a[1]=="User") {
					cout<<"Enter password:";
					string temp_pswd_su;
					cin>>temp_pswd_su;
					getchar();
					if(temp_pswd_su==system_data[1]) USR="User";
				}
				else if(a[1]=="Hit"){
					cout<<"Enter password:";
					string temp_pswd_su1;
					cin>>temp_pswd_su1;
					getchar();
					if(temp_pswd_su1==system_data[0]) USR="Hit";
				}
				else if(a[1]=="Visitor") USR="Visitor";
			}
		}
		else if(a[0]=="cle"){
			system("cls");
		}
		else if(a[0]=="cal"){
			calc_f(a[1],a[2],a[3]);
		}
		else if(a[0]=="allcmd"){
			allcmd_f();
		}
		else if(a[0]=="help"){
			help_f(a[1]);
		}
		else if(a[0]=="gmh"){
			game_f();
		}
		else cout<<"\r\nCommand not found.";
	}
	return 0;
}