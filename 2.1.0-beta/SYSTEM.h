#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <functional>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <filesystem>

#include "UI.h"

using namespace std;
namespace fs = std::filesystem;

string sha(string str) {
    hash<string> hash_fn;
    size_t hash_value = hash_fn(str);
    stringstream ss;
    ss<<hex<<hash_value;
    return ss.str();
}

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
		int de=mkdir("C:\\ProgramData\\Hitmux");
		if(de!=0){
			printf("#002Error! System file does not exist or cannot be opened!\nPlease restart with administrator rights or contact caokai674@gmail.com to solve the problem!");
			while(1) getchar();
		}
		ofstream outfile("C:\\ProgramData\\Hitmux\\data.hit");
		outfile<<sha("NULL")<<"\n";
		outfile<<sha("NULL")<<"\n";
		outfile<<sha("NULL")<<"\n";
		outfile<<sha("NULL")<<"\n";
		outfile<<sha("NULL")<<"\n";
		outfile<<sha("NULL")<<"\n";
		outfile<<sha("NULL")<<"\n";
		outfile<<sha("NULL")<<"\n";
		outfile<<sha("NULL")<<"\n";
		outfile.flush();
		outfile.close();
		return;
	}
	else{
		ifstream fin("C:\\ProgramData\\Hitmux\\data.hit");
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
	ofstream outfile("C:\\ProgramData\\Hitmux\\data.hit");
	for(int i=0;i<8;i++){
		outfile<<system_data[i]<<"\n";
	}
	outfile.flush();
	outfile.close();
}

inline void su_f(string *a,string &USR,string *system_data){
	if(a[1]!="\0"){
		if(USR=="Hit"){
			if(a[1]=="Hit"||a[1]=="User"||a[1]=="Visitor"){
				USR=a[1];
			}
			else printf("There is no such user!");
		}
		else if(a[1]=="User") {
			string temp_pswd_su;
			temp_pswd_su=input_ui_passwd("Enter password:");
			if(sha(temp_pswd_su)==system_data[1]) USR="User";
			else printf("Wrong password!");
		}
		else if(a[1]=="Hit"){
			string temp_pswd_su1;
			temp_pswd_su1=input_ui_passwd("Enter password:");
			if(sha(temp_pswd_su1)==system_data[0]) USR="Hit";
			else printf("Wrong password!");
		}
		else if(a[1]=="Visitor") USR="Visitor";
		else printf("There is no such user!");
	}
	else printf("No user entered!");
}

inline void pswd_f(string *a,string &USR,string *system_data){
	if(a[1]=="Hit"&&USR=="Hit"){
		string temp_pswd;
		temp_pswd=input_ui_passwd("Enter password:");
		if(temp_pswd==input_ui_passwd("Enter again:")){
			system_data[0]=sha(temp_pswd);
			printf("Succeed!");
		}
		else text_ui("Error!",0);
	}
	else if(USR=="Visitor") cout<<"Permission denied.";
	else if(a[1]=="User"&&(USR=="Hit"||USR=="User")){
		string temp_pswd1;
		temp_pswd1=input_ui_passwd("Enter password:");
		if(temp_pswd1==input_ui_passwd("Enter again:")){
			system_data[1]=sha(temp_pswd1);
			printf("Succeed!");
		}
		else text_ui("Error!",0);
	}
	else if(a[1]=="\0") printf("No user entered!");
	else if(a[1]=="Visitor") printf("This user has no password.");
	else if(a[1]!="User"&&a[1]!="Hit") printf("There is no such user!");
	else printf("Error!");
}

inline void rm_f(string *a,string USR){
	if(USR!="Hit"&&USR!="User") printf("Permission denied.");
	else if(a[1]=="-s"&&a[2]!="\0"){
		int re_rm=remove(a[2].c_str());
		if(re_rm==0) printf("Succeed!");
		else printf("Can't remove this file!");
	}
	else if(a[1]=="-r"&&a[2]!="\0"){
		int re_rm1=rmdir(a[2].c_str());
		if(re_rm1==0) printf("Succeed!");
		else printf("Can't remove this folder!");
	}
	else printf("Error!");
}

bool copy_file(const string& source,const string& destination){
    ifstream src(source,ios::binary);
    if(!src){
		printf("Please confirm whether the file exists.\nOr an unknown error has occurred. You can try to start Hitmux as a Windows administrator.");
        return 0;
    }
    ofstream dst(destination,ios::binary);
    if(!dst){
		printf("Please confirm whether the file exists.\nOr an unknown error has occurred. You can try to start Hitmux as a Windows administrator.");
        return 0;
    }
    dst<<src.rdbuf();
    return 1;
}

bool move_file(const string& source,const string& destination){
    if(rename(source.c_str(),destination.c_str())!=0){
		printf("Please confirm whether the file exists.\nOr an unknown error has occurred. You can try to start Hitmux as a Windows administrator.");
        return 0;
    }
    return 1;
}

// bool move_folder(const string& source,const string& destination){
//     try{
//         if(fs::exists(source)&&fs::is_directory(source)){
//             fs::rename(source,destination);
//             return 1;
//         }
// 		else{
//             return 0;
//         }
//     }
// 	catch(const fs::filesystem_error& e){
// 		printf("An unknown error has occurred. You can try to start Hitmux as a Windows administrator.");
//         return 0;
//     }
// }

bool move_folder(const string& source,const string& destination){
    try{
        if(fs::exists(source)&&fs::is_directory(source)){
            if(fs::exists(destination)){
				printf("Destination folder already exists.");
                 return 0;
            }
            fs::rename(source,destination);
            return 1;
        }
		else{
            printf("Source folder does not exist or is not a directory.");
            return false;
        }
    }
	catch(const fs::filesystem_error& e){
        cout<<"An error occurred:"<<e.what()<<endl;
        cout<<"You can try to run as administrator."<<endl;
        return 0;
    }
}


bool copy_folder(const string& source,const string& destination){
    try{
        if(fs::exists(source)&&fs::is_directory(source)){
			if (!fs::exists(destination)) {
                fs::create_directory(destination);
            }
            for(const auto& entry:fs::directory_iterator(source)){
                const auto& path = entry.path();
                const auto& dest_path = fs::path(destination)/path.filename();
                if(fs::is_directory(path)){
                    if(!copy_folder(path.string(),dest_path.string())){
                        return 0;
                    }
                }
				else{
                    fs::copy(path, dest_path);
                }
            }
            return 1;
        }
		else{
			printf("Source folder does not exist or is not a directory.");
            return 0;
        }
    }
	catch(const fs::filesystem_error& e){
		printf("An unknown error has occurred. You can try to start Hitmux as a Windows administrator.");
        return 0;
    }
}

inline void mv_f(string *a,string USR){
	if(USR!="Hit"&&USR!="User") printf("Permission denied.");
	else if(a[1]=="-s"&&a[2]!="\0"){
		if(move_file(a[2],a[3])) printf("Succeed!");
	}
	else if(a[1]=="-r"&&a[2]!="\0"){
		if(move_folder(a[2],a[3])) printf("Succeed!");
	}
	else printf("Error!");
}

inline void cp_f(string *a,string USR){
	if(USR!="Hit"&&USR!="User") printf("Permission denied.");
	else if(a[1]=="-s"&&a[2]!="\0"){
		if(copy_file(a[2],a[3])) printf("Succeed!");
	}
	else if(a[1]=="-r"&&a[2]!="\0"){
		if(copy_folder(a[2],a[3])) printf("Succeed!");
	}
	else printf("Error!");
}

#endif
