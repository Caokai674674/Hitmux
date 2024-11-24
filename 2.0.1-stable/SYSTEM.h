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


void r_init_f(string* system_data){
	if(!canw_f("C:\\ProgramData\\Hitmux\\data.hit")){
//		cout<<"Error! System file does not exist or cannot be opened!\nPlease restart with administrator rights or contact caokai674@gmail.com to solve the problem!";
		// string temp_fs="C:\\Hitmux";
		// const char* temp_fsc=temp_fs.c_str();
		int de=mkdir("C:\\ProgramData\\Hitmux");
		if(de!=0){
			printf("#002Error! System file does not exist or cannot be opened!\nPlease restart with administrator rights or contact caokai674@gmail.com to solve the problem!");
			while(1) getchar();
		}
		// temp_fs+="\\data.hit";
		// const char* temp_fsc1=temp_fs.c_str();
		ofstream outfile("C:\\ProgramData\\Hitmux\\data.hit");
		outfile<<"NULL\n";
		outfile<<"NULL\n";
		outfile<<"NULL\n";
		outfile<<"NULL\n";
		outfile<<"NULL\n";
		outfile<<"NULL\n";
		outfile<<"NULL\n";
		outfile<<"NULL\n";
		outfile<<"NULL\n";
		outfile.flush();
		outfile.close();
		return;
	}
	else{
		// string temp_fs="C:\\ProgramData\\Hitmux\\data.hit";
		// const char* temp_fc=temp_fs.c_str();
		// freopen("C:\\ProgramData\\Hitmux\\data.hit","r",stdin);
		ifstream fin("C:\\ProgramData\\Hitmux\\data.hit");
		// std::ofstream outfile("C:\\ProgramData\\Hitmux\\data.hit");
		for(int i=0;i<8;i++){
			fin>>system_data[i];
		}
		fin.close();
		return;
	}
}

void w_init_f(string* system_data){
	if(!canw_f("C:\\ProgramData\\Hitmux\\data.hit")){
		printf("#001Error! System file does not exist or cannot be opened!\nPlease restart with administrator rights or contact caokai674@gmail.com to solve the problem!");
		while(1) getchar();
	}
	string temp_fs="C:\\ProgramData\\Hitmux\\data.hit";
	const char* temp_fc=temp_fs.c_str();
	// freopen(temp_fc,"w",stdout);
	ofstream outfile("C:\\ProgramData\\Hitmux\\data.hit");
	for(int i=0;i<8;i++){
		outfile<<system_data[i]<<"\n";
	}
	outfile.flush();
	outfile.close();
}

#endif
