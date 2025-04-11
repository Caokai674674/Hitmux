#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <regex>
#include <cstdlib>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/types.h>
    #include <dirent.h>
#endif
#include "safe/sha256.cpp"
#include "../const.cpp"
#include "fs.cpp"
#include "../user/passwd.cpp"

using namespace std;


bool if_install(){
    ifstream install_system(init_file.c_str());
    string evn_file = init_dir + "hitmux.evn";
    ifstream evn_system(evn_file.c_str());

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
    if (MAX_EVN < 7) {
        cout << "Error: MAX_EVN is too small\n";
        cout << "Press any key to exit..." << endl;
        getchar();
        exit(-1);
        return;
    }
    if(if_install()){
        return;
    }
    else{
        hitmuix_basic_mkdir(init_dir,0);
#ifdef _WIN32
        string evn_file = init_dir + "\\hitmux.evn";
#else
        hitmuix_basic_mkdir(init_dir + "/hitmux.evn",0);
        string evn_file = init_dir + "/hitmux.evn";
#endif
        
        ofstream evn_system(evn_file.c_str());
        string sw_path = init_dir;
//         cout << "Please input your sw PATH: \n";
//         cin >> sw_path;
//         if (sw_path.empty()) {
//             cout << "Error: sw path is empty\n";
//             cout << "Press any key to exit..." << endl;
//             getchar();
//             exit(-1);
//             return;
//         }
//         else if (sw_path[0]!= '/') {
//             cout << "Error: sw path is not absolute\n";
//             cout << "Press any key to exit..." << endl;
//             getchar();
//             exit(-1);
//             return;
//         }
//         if (!canWriteToDirectory(sw_path)) {
//             cout << "Error: cannot write to sw path\n";
//             cout << "Press any key to exit..." << endl;
//             getchar();
//             exit(-1);
//             return;
//         }
#ifdef _WIN32
        if (sw_path[sw_path.length() - 1] != '\\') {
            sw_path += "\\";
        }
        evn_system << sw_path << endl;
        evn_system << sw_path << "bin\\" << endl;
        evn_system << sw_path << "lib\\" << endl;
        evn_system << sw_path << "config\\" << endl;   //Debuging : 环境变量中文件只有一个反斜杠！！！
        evn_system << sw_path << "data\\" << endl;
#else
        if (sw_path[sw_path.length() - 1] != '/') {
            sw_path += "/";
        }
        evn_system << sw_path << endl;
        evn_system << sw_path << "bin/" << endl;
        evn_system << sw_path << "lib/" << endl;
        evn_system << sw_path << "config/" << endl;
        evn_system << sw_path << "data/" << endl;
#endif
        
        evn_system << Hitmux_Version << endl;
        evn_system.close();
        

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

bool canWriteToDirectory(const std::string& dirPath) {
    struct stat statbuf;

    if (stat(dirPath.c_str(), &statbuf) != 0) {
        return false;
    }

    if (!S_ISDIR(statbuf.st_mode)) {
        return false;
    }

    std::string testFile = dirPath + "/.write_test.tmp";
    int fd = open(testFile.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        return false;
    }

    if (write(fd, "test", 4) == -1) {
        close(fd);
        return false;
    }

    close(fd);
    testFile.c_str();
    return true;
}

#endif