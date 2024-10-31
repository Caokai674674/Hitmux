#ifndef UI_H
#define UI_H

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <thread>

using namespace std;

inline void SetConsoleColor(int color){
	HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,color);
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

inline void start(){
	for(int i=1;i<=100;i++) {
		cout<<"loading..."<<i<<"%\n";
		system("cls");
	}
	cout<<"Please wait...\n";
	loading(30);
	cout<<"\nHitmux 1.1.0-bate (C) 2024 CaoKai,All right reserved.\n";
	cout<<"Hitmux 1.1.0-bate (C) 2024 CaoKai,All right reserved.\n";
	cout<<"Hitmux 1.1.0-bate (C) 2024 CaoKai,All right reserved.\n\n";
	cout<<"#    #\n";
	cout<<"#    #  #    #\n";
	cout<<"######     ##### ##### #  # #   #\n";
	cout<<"#    #  #    #   # # # #  #   #\n";
	cout<<"#    #  #    ##  # # # #### #   #  1.1.0-bate\n";
	cout<<"Author:CaoKai in Nazi Germany.\nEmail:caokai674@gmail.com\n";
	Sleep(1);
	cout<<"\n\n";
}

inline void shutdown(){
	cout<<"I will shutdown your Hitmux system.";
	cout<<"Please wait...\n";
	loading(20);
	cout<<"\nRemove temp data...\n";
	cout<<"Shutdown system...\n";
	Sleep(1);
}
#endif