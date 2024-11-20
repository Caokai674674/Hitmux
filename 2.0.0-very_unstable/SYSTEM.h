#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

bool canw_f(const string& filename){
    ofstream file(filename,ios::app);
    if(file){
        file.close();
        return 1;
    }
    return 0;
}

string gsd_f(){
    char systemPath[MAX_PATH];
    if (GetSystemDirectory(systemPath,MAX_PATH)){
    	systemPath[1]=':';
    	systemPath[2]='\\';
    	string systemPath_temp="";
    	systemPath_temp+=systemPath[0];
    	systemPath_temp+=systemPath[1];
    	systemPath_temp+=systemPath[2];
        return systemPath_temp;
    }
}

void r_init_f(string* system_data){
	if(!canw_f("C:\\Hitmux\\data.hit")){
//		cout<<"Error! System file does not exist or cannot be opened!\nPlease restart with administrator rights or contact caokai674@gmail.com to solve the problem!";
		string temp_fs="C:\\Hitmux";
		const char* temp_fsc=temp_fs.c_str();
		int de=mkdir(temp_fsc);
		if(de!=0){
			printf("#002Error! System file does not exist or cannot be opened!\nPlease restart with administrator rights or contact caokai674@gmail.com to solve the problem!");
			while(1) getchar();
		}
		temp_fs+="\\data.hit";
		const char* temp_fsc1=temp_fs.c_str();
		freopen(temp_fsc1,"w",stdout);
		printf("654321\n");
		printf("123456\n");
		printf("NULL\n");
		printf("NULL\n");
		printf("NULL\n");
		printf("NULL\n");
		printf("NULL\n");
		printf("NULL\n");
		fclose(stdout);
		freopen("CON","w",stdout);
		fflush(stdout);
		return;
	}
	else{
		string temp_fs="C:\\Hitmux\\data.hit";
		const char* temp_fc=temp_fs.c_str();
		freopen(temp_fc,"r",stdin);
		for(int i=0;i<8;i++){
			cin>>system_data[i];
		}
		fclose(stdin);
		freopen("CON","r",stdin);
		fflush(stdin);
		return;
	}
}

void w_init_f(string* system_data){
	if(!canw_f("C:\\Hitmux\\data.hit")){
		printf("#001Error! System file does not exist or cannot be opened!\nPlease restart with administrator rights or contact caokai674@gmail.com to solve the problem!");
		while(1) getchar();
	}
	string temp_fs="C:\\Hitmux\\data.hit";
	const char* temp_fc=temp_fs.c_str();
	freopen(temp_fc,"w",stdout);
	for(int i=0;i<8;i++){
		printf("%s\n",system_data[i].c_str());
	}
	fclose(stdout);
	freopen("CON","w",stdout);
	fflush(stdout);
}

#endif
