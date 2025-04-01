#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <regex>
#include "safe/sha256.cpp"
#include "../const.cpp"
#include "fs.cpp"
#include "../user/passwd.cpp"

using namespace std;


bool if_install(){
    ifstream install_system(init_file.c_str());
    if(install_system.is_open()){
        string line;
        regex pattern("^[^:]+:[^:]+$");
        while (getline(install_system, line)) {
            if (regex_match(line, pattern)) {
                return true;

            }
        }
        return false;
    }
    else return false;
}

void system_init(){
    if(if_install()){
        return;
    }
    else{
        hitmuix_basic_mkdir(init_dir,0);
        ofstream clean(init_file.c_str());  
        clean.close();
        printf("installing Hitmux system...\n");
        printf("Please input your username and password\n");
        printf("Username:");
        string username, password;
        int flag1;
        while (1){
            flag1 = 1;
            cin >> username;
            for(int i=0;i<username.length();i++){
                if(username[i] == ':'){
                    printf("Invalid username\nPlease input your username again:\n");
                    flag1 = 0;
                    break;
                }
            }
            if(flag1 == 1) break;
        }
        printf("Password:");
        while (1){
            flag1 = 1;
            password = hitmux_input_passwd();
            for(int i=0;i<password.length();i++){
                if(password[i] == ':'){
                    printf("Invalid password\nPlease input your password again:\n");
                    flag1 = 0;
                    break;
                }
            }
            if(flag1 == 1) break;
        }
        ofstream install_system(init_file.c_str());
        install_system << username <<":"<< sha256(password) << "\n";
        install_system.close();
        printf("Hitmux system installed successfully!\n");
    }
}

#endif